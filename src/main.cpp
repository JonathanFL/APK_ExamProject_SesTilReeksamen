#include "include/algorithms/select_random_if.hpp"
#include "include/dbloader/PokemonLoader.hpp"
#include "include/poke_bag/pokeBag.hpp"
#include "include/poke_bag/pokeBagItem.hpp"
#include "include/poke_center.hpp"
#include "include/pokemon/pokemon.hpp"
#include "include/poke_center.hpp"
#include "include/poke_bag/ball/ball.hpp"
#include <boost/variant.hpp>
#include <boost/bind.hpp>
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

  bool exit = false;
  bag.addPokemon(p2);
  // for(auto &p : pokemons)
  // {
  //   bag.addPokemon(p);
  // }
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

    Pokemon p1(100.2, 10, 0, 50, 100, "Squirtle", "Jonathan",
               poketypes::WaterPokemonType());
    //   std::cout << p1 << "\n";
    Pokemon p2(100.2, 10, 0, 50, 100, "Diglet", "Valle",
               poketypes::PokemonTypeVariant(poketypes::WaterPokemonType()),
               poketypes::PokemonTypeVariant(poketypes::GrassPokemonType()));

    std::cout << pokemons[0].getModifier(pokemons[1]) << std::endl;

    PokeBag    bag;
    PokeCenter::Center pokeCenter;
    pokeCenter.ListAvailableItems();
    auto ball = pokeCenter.BuyBall();
    std::cout << std::to_string(ball.get()->getPrice()) << std::endl;
    
    return 0;
}
