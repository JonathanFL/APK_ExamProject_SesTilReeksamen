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
#include "include/dbloader/PokemonListEntry.hpp"

#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <variant>

int main()
{
  std::map<std::string, PokemonList> pokemons;
  dbloader::PokemonLoader pokemonLoader;

  try
  {
    pokemonLoader.ReadPokemonsList(PokemonListEntry::LowLevelPokemons, PokemonListEntry::MediumLevelPokemons, PokemonListEntry::HighLevelPokemons, PokemonListEntry::RarePokemons, PokemonListEntry::UserPokemons);
    pokemons = pokemonLoader.getPokemons();
    pokemonLoader.PrintPokemonList(pokemons[PokemonListEntry::RarePokemons]);
    pokemonLoader.PrintPokemonList(pokemons[PokemonListEntry::UserPokemons]);
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
  // pokecenter.listAvailableItems();
  // auto potion = pokecenter.buyBall();
  // auto p = potion.get();
  // p->Use(pokemons[PokemonListEntry::UserPokemons].at(0),[](PokeBagItemResult result) {
  //       std::cout << result.result << "\n";
  //     });
  // std::cout << pokemons[PokemonListEntry::UserPokemons].at(0) << std::endl;

  bool exit = false;
  try
  {
    bag.addPokemon(pokemons[PokemonListEntry::UserPokemons].at(0));
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
          Utilities::select_random_if(pokemons[PokemonListEntry::RarePokemons].begin(), pokemons[PokemonListEntry::RarePokemons].end(),
                                      [](const Pokemon &p) { return p.getHealth_() > 0; });
      if (randomPokemon == pokemons[PokemonListEntry::RarePokemons].end())
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
