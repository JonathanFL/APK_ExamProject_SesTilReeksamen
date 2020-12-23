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
#include "include/poke_center.hpp"
#include "include/pokemon/pokemon.hpp"
#include "include/algorithms/select_random_if.hpp"

#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <variant>

#define POKEMONS_DB_FILE "config/pokemons.db"

int main()
{
  PokemonList             wildPokemons;
  dbloader::PokemonLoader pokemonLoader;

  try
  {
    pokemonLoader.ReadPokemonsList(POKEMONS_DB_FILE);
    wildPokemons = pokemonLoader.getPokemons();
    pokemonLoader.PrintPokemonList(wildPokemons);
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
              poketypes::FirePokemonType(), poketypes::ElectricPokemonType());
  PokeBag bag;

  // PokeCenter::Center pokecenter;
  // pokecenter.ListAvailableItems();
  // auto potion = pokecenter.BuyPotion();
  // auto p = potion.get();
  // p->Use(p2,[](PokeBagItemResult result) {
  //       std::cout << result.result << "\n";
  //     });
  // std::cout << p2 << std::endl;
  
  bool exit = false;
  bag.addPokemon(p2);
  Player player("Ash", bag);
  while (!exit) // Game loop
  {
    PokemonList::iterator randomPokemon =
        select_random_if(wildPokemons.begin(), wildPokemons.end(),
                         [](const Pokemon &p) { return p.getHealth_() > 0; });
    battle::playBattle(&player, &*randomPokemon);
    if (!player.canBattle())
    {
      std::cout << "You either have no pokemon, or they have all fainted."
                << std::endl;
    }
  }

  return 0;
}
