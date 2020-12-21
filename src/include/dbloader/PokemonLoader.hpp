#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "../pokemon/pokemon.hpp"
#include "FileNotFoundException.hpp"

namespace dbloader
{
    using namespace poketypes;

    class PokemonLoader
    {
    private:
        PokemonList pokemonList_;

    public:
        PokemonLoader(){};
        ~PokemonLoader(){};

        void ReadPokemonsList(const std::string &fileName)
        {
            pokemonList_.clear();
            std::ifstream pokemonsFile(fileName.c_str());

            if (!pokemonsFile)
            {
                throw FileNotFoundException(fileName);
            }

            std::istream_iterator<Pokemon> it1(pokemonsFile);
            std::istream_iterator<Pokemon> it2;

            std::copy(it1, it2, std::back_inserter(pokemonList_));
        }

        void PrintPokemonList(const PokemonList &pl)
        {
            std::ostream_iterator<Pokemon> it1(std::cout);
            std::copy(pl.begin(), pl.end(), it1);
        }

        PokemonList &&getPokemons()
        {
            return std::move(pokemonList_);
        }
    };
} // namespace dbloader
