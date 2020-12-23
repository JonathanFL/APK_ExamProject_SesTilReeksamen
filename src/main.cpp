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
#include "include/algorithms/select_random_if.hpp"

#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <variant>

#define WILD_POKEMONS_DB_FILE "config/pokemons.db"
#define USER_POKEMONS_DB_FILE "config/pokemons.db"

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

  bool exit = false;
  bag.addPokemon(wildPokemons[user].at(0));
  Player player("Ash", bag);
  while (!exit) // Game loop
  {
    PokemonList::iterator randomPokemon =
        select_random_if(wildPokemons[wild].begin(), wildPokemons[wild].end(),
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
