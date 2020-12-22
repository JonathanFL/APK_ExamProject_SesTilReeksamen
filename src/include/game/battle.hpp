#ifndef BATTLE_HPP
#define BATTLE_HPP
#include "../threading/create_thread.hpp"
#include "player.hpp"

#include "future"
#include <boost/signals2.hpp>
#include <future>
#include <iostream>
#include <thread>

namespace battle
{

template <typename T> class PrintContainer
{
public:
  typedef T value_type;
  using iterator = typename std::back_insert_iterator<PrintContainer>;
  void push_back(const T &value) { std::cout << value << std::endl; }
};

template <typename Container> struct aggregate_output
{
  typedef Container result_type;

  template <typename InputIterator>
  Container operator()(InputIterator first, InputIterator last) const
  {
    Container                    c;
    typename Container::iterator it(c);
    std::copy(first, last, it);
    return c;
  }
};
typedef boost::signals2::signal<std::string(),
                                aggregate_output<PrintContainer<std::string>>>
                                   BattleCrySignal;
typedef BattleCrySignal::slot_type BattleCrySlot;
class BattleCry
{
private:
  BattleCrySignal battleCrySignal_;

public:
  void add(const BattleCrySlot &cb) { battleCrySignal_.connect(cb); }
  void operator()() { battleCrySignal_(); }
};

struct PlayerBattleTag
{
};
struct PokemonBattleTag
{
};

template <typename T1, typename T2> void playBattle(T1 *t1, T2 *t2)
{
  battleImpl(t1, t2,
             typename IfThenElse<PlayerBattleTag, PokemonBattleTag,
                                 IsSame<T1, T2>::value>::Type());
}
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
  bool      battleFinished = false;
  BattleCry bc;
  auto      choosePokemonLambda = [player](std::promise<Pokemon &>&& p) {
    Pokemon &pokemon = player->choosePokemon();
    p.set_value_at_thread_exit(pokemon);
  };
//   std::promise<Pokemon &> p;
//   std::future<Pokemon &>  f = p.get_future();
//   std::thread(choosePokemonLambda, std::move(p)).detach();
  std::future<Pokemon &> chosenPokemonFuture =
      createFuture<Pokemon &>(choosePokemonLambda);
  chosenPokemonFuture.wait();
  Pokemon &chosenPokemon = chosenPokemonFuture.get();
  bc.add(std::bind(&Pokemon::battleCry, pokemon));
  bc.add(std::bind(&Pokemon::battleCry, chosenPokemon));
  do
  {
    bc();
    battleFinished = true;
  } while (!battleFinished);
}

template <typename T> class Attack
{
private:
  T attacker_;

public:
  Attack(T &attacker) : attacker_(attacker) {}
  void doAttack(Pokemon &p);
};

} // namespace battle

#endif