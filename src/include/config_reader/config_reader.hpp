#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "pokemon_dto.hpp"
#include "../pokemon.hpp"

typedef std::vector<PokemonDto> PokemonList; 

class ConfigReader
{
private:
    // std::vector<std::string> pl;
    // std::string fileName;

public:
    ConfigReader()
    {
        // fileName = POKEMONS_DB_FILE;
    }
    ~ConfigReader(){};

    void ReadPokemonsList(PokemonList &pl, const std::string &fileName)
    {
        pl.clear();
        std::ifstream pFile(fileName.c_str());

        if (!pFile) 
        {
		    std::cerr << "!!unable to open the necessary files." << std::endl;
	    }

        std::istream_iterator<PokemonDto> it1(pFile);
        std::istream_iterator<PokemonDto> it2;

        std::copy(it1, it2, std::back_inserter(pl));
    }

    void PrintPokemonList(const PokemonList &pl)
    {
        // Pokemon<int, poketypes::WaterPokemonType> p(100.2,10,0,50,100,"Jonathan", "Squirtle"); 

        std::ostream_iterator<PokemonDto> it1(std::cout);
        std::copy(pl.begin(), pl.end(), it1);
    }
};

