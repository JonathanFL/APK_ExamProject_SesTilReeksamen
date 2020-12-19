#ifndef BATTLE_HPP
#define BATTLE_HPP
#include "player.hpp"
namespace battle
{


struct PlayerBattleTag
{
};
struct PokemonBattleTag
{
};
template <typename T1, typename T2, typename = void> void battle(T1 *t1, T2 * t2)
{
  battleImpl(
      t1, t2,
      IfThenElse<PlayerBattleTag, PokemonBattleTag, IsSame<T1, T2>::value>::Type);
}
template<typename T1, typename T2> 
void battleImpl(T1 * player1, T2 * player2, PlayerBattleTag);
template<typename T, typename P>
void batttleImpl(T * player, P * pokemon, PokemonBattleTag);


}

#endif