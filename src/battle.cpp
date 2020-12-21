#include "include/game/battle.hpp"
#include "include/poke_bag/ball/ball.hpp"
#include "include/threading/create_thread.hpp"
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
  bool                   battleFinished = false;
  BattleCry         bc;
  std::future<Pokemon *> chosenPokemonFuture =
      createFuture<Pokemon *>([player](std::promise<Pokemon *> p) {
        Pokemon *pointer = player->choosePokemon();
        p.set_value_at_thread_exit(pointer);
      });
  chosenPokemonFuture.wait();
  Pokemon *chosenPokemon = chosenPokemonFuture.get();
  bc.add(std::bind(&Pokemon::battleCry, pokemon));
  bc.add(std::bind(&Pokemon::battleCry, chosenPokemon));
  do
  {
    bc();
  } while (!battleFinished);
}

template <typename T> void Attack<T>::doAttack(Pokemon &p)
{
  p.setHealth_(p.getHealth_() - attacker_.getStrength());
}

// template <> void Attack<Ball>::doAttack(Ball &p)
// {
//   // TODO:
// }

template <> void Attack<Pokemon>::doAttack(Pokemon &p)
{
  p.setHealth_(p.getHealth_() -
               (attacker_.getAttack_() * attacker_.getModifier(p)));
}


} // namespace battle
