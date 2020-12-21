#ifndef BATTLE_HPP
#define BATTLE_HPP
#include "player.hpp"
#include <boost/signals2.hpp>
#include <iostream>
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

template <typename T> class Attack
{
private:
  T attacker_;

public:
  Attack(T &attacker) : attacker_(attacker) {}
  void doAttack(Pokemon &p);
};

// class PokeballAttack : public Attack
// {
// private:
// public:
//   PokeballAttack(Pokeball &pb) : Attack(pb) {}
// };

// class PokemonAttack : public Attack
// {
// private:
//   poketypes::PokemonTypeVariant *pt_;
//   poketypes::PokemonTypeVariant *st_;

// public:
//   PokemonAttack(double strength, poketypes::PokemonTypeVariant *pt,
//                 poketypes::PokemonTypeVariant *st)
//       : Attack(strength), pt_(pt), st_(st)
//   {
//   }
// };

template <typename T> class PrintContainer
{
public:
typedef T value_type;
  using iterator =
      typename std::back_insert_iterator<PrintContainer>;
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
  void              operator()() { battleCrySignal_(); }
};

} // namespace battle

#endif