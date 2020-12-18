#include "include/pokemon.hpp"
#include "include/poke_type.hpp"

int main() {
// double health, unsigned int level, unsigned int xp, double attack, double defense, std::string name, std::string nickname){
        
    Pokemon<poketypes::ElectricPokemonType,poketypes::WaterPokemonType> p(100.2,10,0,50,100,"Jonathan", "Squirtle");  

    return 0;
}