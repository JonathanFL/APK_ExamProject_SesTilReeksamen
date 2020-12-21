#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "../pokemon/pokemon.hpp"

using namespace poketypes;

typedef std::vector<Pokemon> PokemonList;

class ConfigReader
{
private:
    std::string fileName_;

public:
    ConfigReader(const std::string fileName)
    {
        fileName_ = fileName;
    }
    ~ConfigReader(){};

    void ReadPokemonsList(PokemonList &pl)
    {
        pl.clear();
        std::ifstream pFile(fileName_.c_str());

        if (!pFile)
        {
            std::cerr << "!!unable to open the necessary files." << std::endl;
        }

        std::istream_iterator<Pokemon> it1(pFile);
        std::istream_iterator<Pokemon> it2;

        std::copy(it1, it2, std::back_inserter(pl));
    }

    void PrintPokemonList(const PokemonList &pl)
    {
        std::ostream_iterator<Pokemon> it1(std::cout);
        std::copy(pl.begin(), pl.end(), it1);
    }
};
