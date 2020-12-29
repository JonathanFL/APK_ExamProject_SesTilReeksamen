#pragma once
#include <iostream>

#include "battle.hpp"
#include "../poke_bag/pokeBag.hpp"
#include "../poke_center.hpp"
#include "../pokemon/pokemon.hpp"

#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <variant>

#include "../dbloader/PokemonMapEntry.hpp"
#include "../dbloader/PokemonLoader.hpp"
namespace game
{

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
            std::cout << "=================================" << std::endl;
            std::cout << "=  WELCOME TO THE POKEMON GAME  =" << std::endl;
            std::cout << "=           SIMULATOR           =" << std::endl;
            std::cout << "=================================" << std::endl;

            std::cout << std::endl
                      << "Loading game setup..." << std::endl
                      << std::endl;

            try
            {
                pokemonLoader.ReadPokemonsList(PokemonMapEntry::WildPokemons,
                                               PokemonMapEntry::UserPokemons);
                pokemons = pokemonLoader.getPokemons();
                bag_.addPokemons(std::move(pokemons[PokemonMapEntry::UserPokemons]));
            }
            catch (exceptions::UnknownPokemonTypeException &e)
            {
                std::cout << "UnknownPokemonTypeException: " << e.what() << std::endl;
                throw;
            }
            catch (exceptions::FileNotFoundException &e)
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

        void setPokeCenter(std::shared_ptr<PokeCenter::Center> &&center)
        {
            center_ = std::move(center);
        }

        void initPlayer()
        {
            std::string name;
            std::cout << "Enter your player name: ";
            std::cin >> name;

            std::cout << "Welcome to the game " << name << std::endl
                      << std::endl;

            player_.setName(std::move(name));
            player_.setBag(bag_);
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
                    PokemonList::iterator randomPokemon = Utilities::select_random_if(
                        pokemons[PokemonMapEntry::WildPokemons].begin(),
                        pokemons[PokemonMapEntry::WildPokemons].end(),
                        [](const Pokemon &p) { return p.getHealth_() > 0; });
                    if (randomPokemon == pokemons[PokemonMapEntry::WildPokemons].end())
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
                    player_.listBagItems();
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
} // namespace game