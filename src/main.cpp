#include "include/algorithms/select_random_if.hpp"
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

  /*
  PokeCenter::Center pokecenter;
  pokecenter.ListAvailableItems();
  auto ball = pokecenter.BuyBall();
  std::cout << std::to_string(ball.get()->getPrice()) << std::endl;
  */
      
  bool exit = false;
  bag.addPokemon(p2);
  Player player("Ash", bag);
  while (!exit) // Game loop
  {
    std::future<PlayerGameChoice> choiceFuture = player.makeGameChoice();
    choiceFuture.wait();
    PlayerGameChoice choice = choiceFuture.get();
    switch (choice)
    {
    case PlayerGameChoice::GoToPokecenter:
      /* code */
      break;
    case PlayerGameChoice::BattleWildPokemon:
      PokemonList::iterator randomPokemon =
          select_random_if(wildPokemons.begin(), wildPokemons.end(),
                           [](const Pokemon &p) { return p.getHealth_() > 0; });
      if (randomPokemon == wildPokemons.end())
      {
        std::cout << "No wild pokemon left - you have won the game!"
                  << std::endl;
        exit = true;
      }
      else if (!player.canBattle())
      {
        std::cout << "You either have no pokemon, or they have all fainted."
                  << std::endl;
      }
      else
      {
        battle::playBattle(&player, &*randomPokemon);
      }
      break;
    }
  }
  return 0;
}
