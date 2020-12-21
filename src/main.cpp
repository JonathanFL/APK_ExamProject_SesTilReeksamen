#include "include/config_reader/config_reader.hpp"
#include "include/poke_bag/ball/ball.hpp"
#include "include/poke_bag/ball/masterBall.hpp"
#include "include/poke_bag/ball/ultraBall.hpp"
#include "include/poke_bag/potion/hyperPotion.hpp"
#include "include/poke_bag/potion/superPotion.hpp"
#include "include/poke_bag/pokeBag.hpp"
#include "include/poke_bag/pokeBagItem.hpp"
#include "include/pokemon/pokemon.hpp"

#include <boost/variant.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <variant>

#define POKEMONS_DB_FILE "config/pokemons.db"

int main()
{
  Pokemon p1(100.2, 10, 0, 50, 100, "Squirtle", "Jonathan",
             poketypes::PokemonTypeVariant(poketypes::WaterPokemonType()));
             
  Pokemon p2(100.2, 10, 0, 50, 100, "Diglet", "Valle",
             poketypes::PokemonTypeVariant(poketypes::WaterPokemonType()),
             poketypes::PokemonTypeVariant(poketypes::GrassPokemonType()));
  std::cout << p1.getModifier(p2) << std::endl;

  PokemonList  pl;
  ConfigReader cr;

  cr.ReadPokemonsList(pl, POKEMONS_DB_FILE);
  cr.PrintPokemonList(pl);

  PokeBag    bag;
  MasterBall masterBall1;
  MasterBall masterBall2;
  UltraBall  ultraBall;
  SuperPotion superPotion;
  HyperPotion hyperPotion;
  bag.addItem<MasterBall>(&masterBall1);
  bag.addItem<MasterBall>(&masterBall2);
  bag.addItem<UltraBall>(&ultraBall);
  bag.addItem<SuperPotion>(&superPotion);
  bag.addItem<HyperPotion>(&hyperPotion);
  bag.listItems();
  auto item = bag.getItemByIndex(10);
  if (std::holds_alternative<PokeBagItem*>(item)){
    std::get<PokeBagItem*>(item)->Use([]() { 
      std::cout << "Item used\n";
    });
  }
  

  return 0;
}
