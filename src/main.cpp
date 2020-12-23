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

int main()
{
  std::map<std::string, PokemonList> wildPokemons;
  dbloader::PokemonLoader pokemonLoader;

  std::string wild = "config/wild_pokemons.db", user = "config/user_pokemons.db";

  try
  {
    pokemonLoader.ReadPokemonsList(wild, user);
    wildPokemons = pokemonLoader.getPokemons();
    pokemonLoader.PrintPokemonList(wildPokemons[wild]);
    pokemonLoader.PrintPokemonList(wildPokemons[user]);
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

  PokeBag bag;
  PokeCenter::Center center;

  // PokeCenter::Center pokecenter;
  // pokecenter.ListAvailableItems();
  // auto potion = pokecenter.BuyPotion();
  // auto p = potion.get();
  // p->Use(p2,[](PokeBagItemResult result) {
  //       std::cout << result.result << "\n";
  //     });
  // std::cout << p2 << std::endl;

  bool exit = false;
  try
  {
    bag.addPokemon(wildPokemons[user].at(0));
  }
  catch (...)
  {
    std::cout << "caugth an error" << endl;
  }
  Player player("Ash", bag);
  while (!exit) // Game loop
  {
    std::future<PlayerGameChoice> choiceFuture = player.makeGameChoice();
    choiceFuture.wait();
    PlayerGameChoice choice = choiceFuture.get();
    switch (choice)
    {
    case PlayerGameChoice::GoToPokecenter:
      center.usePokecenter(player);
      break;
    case PlayerGameChoice::BattleWildPokemon:
      PokemonList::iterator randomPokemon =
          Utilities::select_random_if(wildPokemons[wild].begin(), wildPokemons[wild].end(),
                           [](const Pokemon &p) { return p.getHealth_() > 0; });
      if (randomPokemon == wildPokemons[wild].end())
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
