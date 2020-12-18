#include "include/ball/ball.hpp"
#include "include/pokemon.hpp"
#include "include/poke_type.hpp"
#include <iostream>

int main() {
// double health, unsigned int level, unsigned int xp, double attack, double defense, std::string name, std::string nickname){
        
    Pokemon<poketypes::GroundPokemonType, poketypes::WaterPokemonType> p1(100.2,10,0,50,100,"Jonathan", "Squirtle");
    std::cout << p1 << "\n";

    Pokemon<poketypes::GroundPokemonType, poketypes::WaterPokemonType> p2;
    std::cout << p2 << std::endl;

    Ball b;

    return 0;
}