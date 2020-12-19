#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "if_then_else.hpp"
#include "../poke_bag/pokeBag.hpp"
#include "pokedex.hpp"
#include <string>
class Player
{
private:
  std::string name_;
  PokeBag     bag_;
  Pokedex     pokedex_;
  void        battleImpl_(IPokemon *pokemon) {}
  void        battleImpl_(Player *player) {}

public:
  template <typename T, typename = void> void battle(T challenger)
  {
    battleImpl(IfThenElse<IPokemon *, Player *, IsSame<T, Player *>>);
  }
  Player(std::string name, PokeBag &&pokeBag, Pokedex &&pokedex) 
  {
      
  }
};

#endif