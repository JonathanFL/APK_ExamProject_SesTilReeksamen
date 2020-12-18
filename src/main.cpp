#include "include/pokemon.hpp"
#include "include/config_reader/config_reader.hpp"
#include "include/poke_type.hpp"
#include <iostream>

#define POKEMONS_DB_FILE "config/pokemons.db"


int main() {
// double health, unsigned int level, unsigned int xp, double attack, double defense, std::string name, std::string nickname){
        
    // Pokemon<poketypes::ElectricPokemonType, poketypes::WaterPokemonType> p(100.2,10,0,50,100,"Jonathan", "Squirtle"); 

    Pokemon<poketypes::GroundPokemonType, poketypes::WaterPokemonType> p1(100.2,10,0,50,100,"Jonathan", "Squirtle");
    std::cout << p1 << "\n";

    Pokemon<poketypes::GroundPokemonType, poketypes::WaterPokemonType> p2;
    std::cout << p2 << std::endl;

    PokemonList pl;

    ConfigReader cr;

    cr.ReadPokemonsList(pl, POKEMONS_DB_FILE);
    cr.PrintPokemonList(pl);
    
    return 0;
}