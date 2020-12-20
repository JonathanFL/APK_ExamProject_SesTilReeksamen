#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "../metaprogramming/if_then_else.hpp"
#include "../poke_bag/pokeBag.hpp"
#include "../pokemon/pokedex.hpp"
#include "battle.hpp"
#include <string>

class Player
{
private:
  std::string name_;
  PokeBag     bag_;
  Pokedex     pokedex_;

public:

  Player(std::string name, PokeBag &&pokeBag, Pokedex &&pokedex) : bag_(std::move(pokeBag)), pokedex_(std::move(pokedex))
  {
      
  }
};

#endif