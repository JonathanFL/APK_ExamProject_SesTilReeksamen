#ifndef BATTLE_HPP
#define BATTLE_HPP
#include "player.hpp"
#include <boost/signals2.hpp>
namespace battle
{

struct PlayerBattleTag
{
};
struct PokemonBattleTag
{
};
template <typename T1, typename T2, typename = void> void battle(T1 *t1, T2 *t2)
{
  battleImpl(t1, t2,
             IfThenElse<PlayerBattleTag, PokemonBattleTag,
                        IsSame<T1, T2>::value>::Type);
}
template <typename T1, typename T2>
void battleImpl(T1 *player1, T2 *player2, PlayerBattleTag);
template <typename T, typename P>
void battleImpl(T *player, P *pokemon, PokemonBattleTag);

// template <typename PT, typename ST> class Attack
// {
// private:
//   int strength_;

// public:
//   Attack(int strength) : strength_(strength) {}
//   typedef PT PrimaryType;
//   typedef ST SecondaryType;
//   int        getStrength() { return strength_; }
//   typedef typename boost::signals2::signal<void(Attack<PT, ST>)>::signature_type
//       type;
// };

template <typename PT1, typename ST1, typename PT2, typename ST2>
class BattleMediator
{
private:
  boost::signals2::signal<void()> battleFinishedSignal;
  boost::signals2::signal<void()> battleStartedSignal;
  typedef typename boost::signals2::signal<void(Pokemon &)>::signature_type
      p1TurnType;
  typedef typename boost::signals2::signal<void(Pokemon &)>::signature_type
      p2TurnType;
  boost::signals2::signal<p1TurnType>             p1TurnSignal;
  boost::signals2::signal<p2TurnType>             p2TurnSignal;
  boost::signals2::signal<Attack<PT1, ST1>::type> p1DefendSignal;
  boost::signals2::signal<Attack<PT2, ST2>::type> p2DefendSignal;

public:
  template <typename BFS, typename BSS>
  void participateP1(BFS &bfs, BSS &bss, p1TurnType tt);
  template <typename BFS, typename BSS>
  void participateP2(BFS &bfs, BSS &bss, p2TurnType tt);
  void attackP1()
};

} // namespace battle

#endif