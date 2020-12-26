// #include "include/dbloader/PokemonLoader.hpp"
// #include "include/game/battle.hpp"
// #include "include/poke_bag/ball/ball.hpp"
// #include "include/poke_bag/ball/masterBall.hpp"
// #include "include/poke_bag/ball/ultraBall.hpp"
#include "include/poke_bag/pokeBag.hpp"
// #include "include/poke_bag/pokeBagItem.hpp"
// #include "include/poke_bag/potion/hyperPotion.hpp"
// #include "include/poke_bag/potion/superPotion.hpp"
#include "include/poke_center.hpp"
// #include "include/pokemon/pokemon.hpp"
// #include "include/dbloader/PokemonListEntry.hpp"

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

  std::shared_ptr<PokeCenter::Center> center = std::make_shared<PokeCenter::Center>();

  pokemonGame.setPokeCenter(std::move(center));

  pokemonGame.initPlayer();
  pokemonGame.run();

  return 0;
}
