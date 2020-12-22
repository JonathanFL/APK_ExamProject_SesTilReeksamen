#ifndef BATTLE_HPP
#define BATTLE_HPP
#include "../poke_bag/ball/ball.hpp"
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

template <typename T> class Attack
{
private:
  T attacker_;

public:
  Attack(T &attacker) : attacker_(attacker) {}
  template <typename T1 = T>
  typename std::enable_if<IsSame<T1, Pokemon>::value, std::string>::type
  doAttack(Pokemon &p)
  {
    double modifier      = attacker_.getModifier(p);
    double currentHealth = p.getHealth_();
    double damage        = attacker_.getAttack_() * modifier;
    currentHealth        -= damage;
    if (currentHealth < 0) currentHealth = 0;
    p.setHealth_(currentHealth);
    std::string effectiveness;
    if (modifier < 0.5)
    {
      effectiveness = "It was very ineffective";
    }
    else if (modifier < 1)
    {
      effectiveness = "It was not very effective";
    } 
    else if(modifier > 1) {
      effectiveness = "It was very effective";
    }
    else if(modifier > 1.5) {
      effectiveness = "It was super effective";
    }
    std::string fainted;
    if(currentHealth == 0)
    {
      fainted = p.getNickname_() + " fainted...";
    }
    return attacker_.getNickname_() + " attacked wild " + p.getName_() +
           " for " + std::to_string(damage) + "\n" + effectiveness + "\n" + fainted;
  }
  template <typename T1 = T>
  typename std::enable_if<std::is_base_of<Ball, T1>::value, bool>::type
  doAttack(Pokemon &p)
  {
  }
};

bool hasBattleFinished(Pokemon &p1, Pokemon &p2)
{
  return p1.getHealth_() == 0 || p2.getHealth_() == 0;
}

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
  bool battleFinished = false;
  std::cout << "A wild " << pokemon->getName_() << " appeared!" << std::endl;
  if (!(player->canBattle()))
  {
    std::cout << "You're unable to battle - running from battle..."
              << std::endl;
    return;
  }

  auto choosePokemonLambda = [player](std::promise<Pokemon &> &&p) {
    Pokemon &pokemon = player->choosePokemon();
    p.set_value_at_thread_exit(pokemon);
  };
  std::future<Pokemon &> chosenPokemonFuture =
      createFuture<Pokemon &>(choosePokemonLambda);
  chosenPokemonFuture.wait();
  Pokemon &chosenPokemon = chosenPokemonFuture.get();
  std::cout << "Go " << chosenPokemon.getNickname_() << "!" << std::endl;
  BattleCry bc;
  bc.add(std::bind(&Pokemon::battleCry, pokemon));
  bc.add(std::bind(&Pokemon::battleCry, chosenPokemon));
  bc();
  while (!battleFinished)
  {
    std::future<PlayerBattleChoice> choiceFuture = player->makeChoice();
    // Could do something else while waiting for player choice
    choiceFuture.wait();
    PlayerBattleChoice choice = choiceFuture.get();
    switch (choice)
    {
    case PlayerBattleChoice::Attack:
    {
      std::cout << "Attacking wild pokemon" << std::endl;
      Attack<Pokemon> attack(chosenPokemon);
      std::cout << attack.doAttack(*pokemon) << std::endl;
      break;
    }
    case PlayerBattleChoice::UseItem:
    {
      std::cout << "Using item" << std::endl;
      // TODO:
      break;
    }
    case PlayerBattleChoice::UsePokeball:
    {
      std::cout << "Using pokeball..." << std::endl;
      // TODO::
      break;
    }
    case PlayerBattleChoice::Run:
    {
      std::cout << "Running from battle..." << std::endl;
      battleFinished = true;
      break;
    }
    default:
    {
      break;
    }
    }
    if (!(pokemon->getHealth_() <= 0) && !battleFinished)
    {
      Attack<Pokemon> wildPokemonAttack(*pokemon);
      std::cout << wildPokemonAttack.doAttack(chosenPokemon) << std::endl;
    }
    battleFinished |= hasBattleFinished(chosenPokemon, *pokemon);
  }
}

} // namespace battle

#endif