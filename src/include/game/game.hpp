#include <iostream>

#include "../dbloader/PokemonListEntry.hpp"
#include "../dbloader/PokemonLoader.hpp"

class PokemonGame
{
private:
    static PokemonGame *instance_;
    std::map<std::string, PokemonList> pokemons;
    dbloader::PokemonLoader pokemonLoader;

    PokemonGame(){};

public:
    ~PokemonGame()
    {
        delete instance_;
    };

    PokemonGame *getGameInstance()
    {
        if (!instance_)
        {
            instance_ = new PokemonGame();
        }
        return instance_;
    };

    void loadPokemons()
    {
        try
        {
            pokemonLoader.ReadPokemonsList(PokemonListEntry::LowLevelPokemons, PokemonListEntry::MediumLevelPokemons, PokemonListEntry::HighLevelPokemons, PokemonListEntry::RarePokemons, PokemonListEntry::UserPokemons);
            pokemons = pokemonLoader.getPokemons();
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
};