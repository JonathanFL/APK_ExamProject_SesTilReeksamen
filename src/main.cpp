#include "include/poke_bag/pokeBag.hpp"
#include "include/poke_center.hpp"
#include "include/game/game.hpp"

#include <boost/bind.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <variant>

int main()
{
  PokemonGame pokemonGame;
  try
  {
    pokemonGame.loadPokemons();
  }
  catch (...)
  {
    return 0;
  }

  pokemonGame.setPokeCenter(std::make_shared<PokeCenter::Center>());

  pokemonGame.initPlayer();
  pokemonGame.run();

  return 0;
}
