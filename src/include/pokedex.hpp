#ifndef POKEDEX_HPP
#define POKEDEX_HPP
#include <map>
#include "pokemon.hpp"
class Pokedex {
private:
    std::map<int, IPokemon> pokemons_;
public:
    void print();

    int discovered();

    int undiscovered();

};

#endif