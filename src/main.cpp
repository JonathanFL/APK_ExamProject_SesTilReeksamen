#include "include/dbloader/PokemonLoader.hpp"
#include "include/game/battle.hpp"
#include "include/game/player.hpp"
#include "include/poke_bag/ball/ball.hpp"
#include "include/poke_bag/ball/masterBall.hpp"
#include "include/poke_bag/ball/ultraBall.hpp"
#include "include/poke_bag/pokeBag.hpp"
#include "include/poke_bag/pokeBagItem.hpp"
#include "include/poke_bag/potion/hyperPotion.hpp"
#include "include/poke_bag/potion/superPotion.hpp"
#include "include/pokemon/pokemon.hpp"

#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <variant>

#define POKEMONS_DB_FILE "config/pokemons.db"

int main()
{
  PokemonList             pokemons;
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

  Pokemon p2(100.2, 10, 0, 50, 100, "Charmander", "Valle",
             poketypes::FirePokemonType(),
             poketypes::ElectricPokemonType());
  PokeBag     bag;

  bool        exit        = false;
  for(auto &p : pokemons)
  {
    bag.addPokemon(p);
  }
  Player player("Ash", bag);
  while (!exit) // Game loop
  {
    battle::playBattle(&player, &p2);

    if(!player.canBattle())
    {
      std::cout << "You either have no pokemon, or they have all fainted." << std::endl;
    }
  }

  return 0;
}
