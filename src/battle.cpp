#include "include/game/battle.hpp"
namespace battle
{
template <typename T> void battleImpl(T *player1, T *player2, PlayerBattleTag)
{
  bool battleFinished = false;
  do
  {

  } while (!battleFinished);
}

template <typename T, typename P>
void battleImpl(T *player, P *pokemon, PokemonBattleTag)
{
}

template <typename PT1, typename ST1, typename PT2, typename ST2>
template <typename BFS, typename BSS>
void BattleMediator<PT1, ST1, PT2, ST2>::participateP1<BFS, BSS>(
    BFS &bfs, BSS &bss, BattleMediator<PT1, ST1, PT2, ST2>::p1TurnType tt)
{
    battleFinishedSignal.connect(bfs);
    battleStartedSignal.connect(bss);
    battle
}

template <typename PT1, typename ST1, typename PT2, typename ST2>
template <typename BFS, typename BSS>
void BattleMediator<PT1, ST1, PT2, ST2>::participateP2<BFS, BSS>(
    BFS &bfs, BSS &bss, BattleMediator<PT1, ST1, PT2, ST2>::p2TurnType tt)
{
}
} // namespace battle
