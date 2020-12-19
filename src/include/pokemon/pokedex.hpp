#ifndef POKEDEX_HPP
#define POKEDEX_HPP
#include <map>
#include "boost/variant.hpp"
#include "pokemon.hpp"

class Pokedex {
private:
    std::map<int, boost::variant<std::string, IPokemon>> pokemons_;
public:
    void print();

    int discovered();

    int undiscovered();

};

#endif