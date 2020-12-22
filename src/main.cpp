#include "include/dbloader/PokemonLoader.hpp"
#include "include/poke_bag/ball/ball.hpp"
#include "include/poke_bag/ball/masterBall.hpp"
#include "include/poke_bag/ball/ultraBall.hpp"
#include "include/poke_bag/potion/hyperPotion.hpp"
#include "include/poke_bag/potion/superPotion.hpp"
#include "include/poke_bag/pokeBag.hpp"
#include "include/poke_bag/pokeBagItem.hpp"
#include "include/pokemon/pokemon.hpp"
#include "include/game/player.hpp"
#include "include/game/battle.hpp"

#include <boost/variant.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <variant>

#define POKEMONS_DB_FILE "config/pokemons.db"

int main()
{
  PokemonList pokemons;
  dbloader::PokemonLoader pokemonLoader;

  try
  {
    pokemonLoader.ReadPokemonsList(POKEMONS_DB_FILE);
    pokemons = pokemonLoader.getPokemons();
    pokemonLoader.PrintPokemonList(pokemons);
  }
  catch (poketypes::UnknownPokemonTypeException &e)
  {
    std::cout << "UnknownPokemonTypeException: " << e.what() << std::endl;
    return 0;
  }
  catch (dbloader::FileNotFoundException &e)
  {
    std::cout << "FileNotFoundException: " << e.what() << std::endl;
    return 0;
  }
  catch (...)
  {
    std::cout << "Unknown error on reading pokemons" << std::endl;
    return 0;
  }

  Pokemon p1(100.2, 10, 0, 50, 100, "Squirtle", "Jonathan",
             poketypes::WaterPokemonType());
  //   std::cout << p1 << "\n";
  Pokemon p2(100.2, 10, 0, 50, 100, "Diglet", "Valle",
             poketypes::PokemonTypeVariant(poketypes::WaterPokemonType()),
             poketypes::PokemonTypeVariant(poketypes::GrassPokemonType()));

  PokemonList testPokemons({p1, p2});
  std::cout << p1.getModifier(p2) << std::endl;
  std::cout << p2.getModifier(p1) << std::endl;
  pokemonLoader.PrintPokemonList(testPokemons);

  Pokemon p3(std::move(p2));

  PokemonList testPokemons1({p1, p2, p3});

  std::cout << p1.getModifier(p3) << std::endl;
  std::cout << p2.getModifier(p3) << std::endl;
  std::cout << p3.getModifier(p1) << std::endl;
  std::cout << p3.getModifier(p2) << std::endl;

  pokemonLoader.PrintPokemonList(testPokemons1);
  p3 = std::move(p1);

  PokemonList testPokemons2({p1, p2, p3});

  std::cout << p1.getModifier(p3) << std::endl;
  std::cout << p2.getModifier(p3) << std::endl;
  std::cout << p3.getModifier(p1) << std::endl;
  std::cout << p3.getModifier(p2) << std::endl;

  pokemonLoader.PrintPokemonList(testPokemons2);

  std::cout << pokemons[0].getModifier(pokemons[1]) << std::endl;

  PokeBag bag;
  MasterBall masterBall1;
  MasterBall masterBall2;
  UltraBall ultraBall;
  SuperPotion superPotion;
  HyperPotion hyperPotion;
  bag.addItem<MasterBall>(&masterBall1);
  bag.addItem<MasterBall>(&masterBall2);
  bag.addItem<UltraBall>(&ultraBall);
  bag.addItem<SuperPotion>(&superPotion);
  bag.addItem<HyperPotion>(&hyperPotion);
  bag.listItems();
  auto item = bag.getItemByIndex(1);
  if (std::holds_alternative<PokeBagItem *>(item))
  {
    std::get<PokeBagItem *>(item)->Use([](PokeBagItemResult result) {
      std::cout << result.result;
    });
  }
  bool exit = false;
  bag.addPokemon(p1, p2);
  Player player("Ash", bag);
  while (!exit) //Game loop
  {
    battle::playBattle(&player, &p1);
  }

  return 0;
}
