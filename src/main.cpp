#include "include/poke_bag/ball/ball.hpp"
#include "include/pokemon/pokemon.hpp"
#include "include/config_reader/config_reader.hpp"
#include "include/poke_bag/pokeBagItem.hpp"
#include "include/poke_bag/pokeBag.hpp"
#include "include/poke_bag/pokeBagItem.hpp"
#include "include/poke_bag/ball/masterBall.hpp"
#include "include/poke_bag/ball/ultraBall.hpp"

#include <iostream>

#define POKEMONS_DB_FILE "config/pokemons.db"


int main() {
// double health, unsigned int level, unsigned int xp, double attack, double defense, std::string name, std::string nickname){
        
    Pokemon<poketypes::ElectricPokemonType, poketypes::WaterPokemonType> p(100.2,10,0,50,100,"Jonathan", "Squirtle"); 

    Pokemon<poketypes::GroundPokemonType, poketypes::WaterPokemonType> p1(100.2,10,0,50,100,"Jonathan", "Squirtle");
    std::cout << p1 << "\n";

    Pokemon<poketypes::GroundPokemonType, poketypes::WaterPokemonType> p2;
    std::cout << p2 << std::endl;

    PokemonList pl;

    ConfigReader cr;

    cr.ReadPokemonsList(pl, POKEMONS_DB_FILE);
    cr.PrintPokemonList(pl);
    
    PokeBag bag;
    MasterBall masterBall1;
    MasterBall masterBall2;
    UltraBall ultraBall;
    bag.addItem<MasterBall>(&masterBall1);
    bag.addItem<MasterBall>(&masterBall2);
    bag.addItem<UltraBall>(&ultraBall);
    bag.listItems();

    return 0;
}