#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <future>
#include <thread>
#include "../pokemon/pokemon.hpp"
#include "../exceptions/FileNotFoundException.hpp"

namespace dbloader
{
    using namespace poketypes;

    class PokemonLoader
    {
    private:
        std::map<std::string, PokemonList> pokemonMap_;
        std::map<std::string, std::future<PokemonList>> futures;

    public:
        PokemonLoader(){};
        ~PokemonLoader(){};

        void ReadPokemonsList(const std::string &fileName)
        {
            std::future<PokemonList> futurePokemonList = std::async(std::launch::async, [fileName]() {
                std::string fileDir = "config/" + fileName;
                std::ifstream pokemonsFile(fileDir.c_str());

                if (!pokemonsFile)
                {
                    throw exceptions::FileNotFoundException(fileDir);
                }

                std::istream_iterator<Pokemon> it1(pokemonsFile);
                std::istream_iterator<Pokemon> it2;

                PokemonList pokemonList;

                std::copy(it1, it2, std::back_inserter(pokemonList));
                return pokemonList;
            });

            futures.insert(std::make_pair(fileName, std::move(futurePokemonList)));
        }

        template <typename File, typename... Files>
        void ReadPokemonsList(const File &file, const Files &... files)
        {
            static_assert(IsSame<File, std::string>::value);
            ReadPokemonsList(file);
            ReadPokemonsList(files...);
        }

        void PrintPokemonList(const PokemonList &pl)
        {
            std::ostream_iterator<Pokemon> it1(std::cout);
            std::copy(pl.begin(), pl.end(), it1);
        }

        void getPokemons(std::map<std::string, PokemonList> &pm)
        {
            for (auto &f : futures)
            {
                pokemonMap_.insert(std::make_pair(f.first, f.second.get()));
            }

            pm = std::move(pokemonMap_);
        }
    };
} // namespace dbloader
