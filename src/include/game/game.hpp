#include <iostream>

#include "battle.hpp"
// #include "include/game/player.hpp"
// #include "include/poke_bag/ball/ball.hpp"
// #include "include/poke_bag/ball/masterBall.hpp"
// #include "include/poke_bag/ball/ultraBall.hpp"
#include "../poke_bag/pokeBag.hpp"
// #include "include/poke_bag/pokeBagItem.hpp"
// #include "include/poke_bag/potion/hyperPotion.hpp"
// #include "include/poke_bag/potion/superPotion.hpp"
#include "../poke_center.hpp"
#include "../pokemon/pokemon.hpp"

#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <variant>

#include "../dbloader/PokemonListEntry.hpp"
#include "../dbloader/PokemonLoader.hpp"

class PokemonGame
{
private:
    std::map<std::string, PokemonList> pokemons;
    dbloader::PokemonLoader pokemonLoader;
    PokeBag bag_;
    std::shared_ptr<PokeCenter::Center> center_;
    Player player_;

public:
    PokemonGame(){};
    ~PokemonGame(){};

    void loadPokemons()
    {
        try
        {
            pokemonLoader.ReadPokemonsList(PokemonListEntry::LowLevelPokemons, PokemonListEntry::MediumLevelPokemons, PokemonListEntry::HighLevelPokemons, PokemonListEntry::RarePokemons, PokemonListEntry::UserPokemons);
            pokemons = pokemonLoader.getPokemons();
            bag_.addPokemons(std::forward<PokemonList>(pokemons[PokemonListEntry::UserPokemons]));
        }
        catch (poketypes::UnknownPokemonTypeException &e)
        {
            std::cout << "UnknownPokemonTypeException: " << e.what() << std::endl;
            throw;
        }
        catch (dbloader::FileNotFoundException &e)
        {
            std::cout << "FileNotFoundException: " << e.what() << std::endl;
            throw;
        }
        catch (...)
        {
            std::cout << "Unknown error on reading pokemons" << std::endl;
            throw;
        }
    }

    void setPokeCenter(std::shared_ptr<PokeCenter::Center> center)
    {
        center_ = std::move(center);
    }

    void initPlayer()
    {
        std::string name;
        std::cout << "Enter your name: ";
        std::cin >> name;

        player_.setName(std::forward<std::string>(name));
        player_.setBag(bag_);

        std::cout << "Welcome to the Pokemon Game Simulator " << name << std::endl;
    }

    void run()
    {
        bool exit = false;
        while (!exit) // Game loop
        {
            std::future<PlayerGameChoice> choiceFuture = player_.makeGameChoice();
            choiceFuture.wait();
            PlayerGameChoice choice = choiceFuture.get();
            switch (choice)
            {
            case PlayerGameChoice::GoToPokecenter:
            {
                center_->usePokecenter(player_);
                break;
            }
            case PlayerGameChoice::BattleWildPokemon:
            {
                PokemonList::iterator randomPokemon =
                    Utilities::select_random_if(pokemons[PokemonListEntry::RarePokemons].begin(), pokemons[PokemonListEntry::RarePokemons].end(),
                                                [](const Pokemon &p) { return p.getHealth_() > 0; });
                if (randomPokemon == pokemons[PokemonListEntry::RarePokemons].end())
                {
                    std::cout << "No wild pokemon left - you have won the game!"
                              << std::endl;
                    exit = true;
                }
                else if (!player_.canBattle())
                {
                    std::cout << "You either have no pokemon, or they have all fainted."
                              << std::endl;
                }
                else
                {
                    battle::playBattle(&player_, &*randomPokemon);
                }
                break;
            }
            case PlayerGameChoice::CheckPokemons:
            {
                player_.listPokemon();
                break;
            }
            case PlayerGameChoice::CheckBagItems:
            {
                break;
            }
            case PlayerGameChoice::ExitGame:
            {
                exit = true;
                break;
            }
            }
        }
    }
};