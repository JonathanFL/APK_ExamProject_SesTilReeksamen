#include "include/pokemon/pokedex.hpp"
void Pokedex::print() {}

int Pokedex::discovered() {
    
}

int Pokedex::undiscovered() { return pokemons_.size() - discovered(); }
