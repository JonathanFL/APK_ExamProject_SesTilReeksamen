#ifndef BATTLE_HPP
#define BATTLE_HPP
#include "../poke_bag/ball/ball.hpp"
#include "../threading/create_thread.hpp"
#include "../exceptions/UnknownPokemonException.hpp"
#include "attack.hpp"
#include "battle_cry.hpp"
#include "player.hpp"
#include <future>
#include <iostream>
#include <thread>

namespace battle
{

  struct PlayerBattleTag
  {
  };
  struct PokemonBattleTag
  {
  };

  bool hasBattleFinished(Pokemon &p1, Pokemon &p2)
  {
    return p1.getHealth_() == 0 || p2.getHealth_() == 0;
  }

  template <typename T1, typename T2>
  void playBattle(T1 *t1, T2 *t2)
  {
    battleImpl(t1, t2,
               typename IfThenElse<PlayerBattleTag, PokemonBattleTag,
                                   IsSame<T1, T2>::value>::Type());
  }
  template <typename T>
  void battleImpl(T *player1, T *player2, PlayerBattleTag)
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
    std::cout << "A wild " << pokemon->getName_() << " appeared!" << std::endl
              << std::endl;
    if (!(player->canBattle()))
    {
      std::cout << "You're unable to battle - running from battle..."
                << std::endl;
      return;
    }

    auto choosePokemonLambda = [player](std::promise<Pokemon &> &&p) {
      bool pokemonChosen = false;
      while (!pokemonChosen)
      {
        try
        {
          Pokemon &pokemon = player->choosePokemon();
          p.set_value_at_thread_exit(pokemon);
          pokemonChosen = true;
        }
        catch (const UnknownPokemonException &e)
        {
          std::cerr << e.what() << std::endl
                    << std::endl;
        }
      }
    };

    std::future<Pokemon &> chosenPokemonFuture = createFuture<Pokemon &>(choosePokemonLambda);
    chosenPokemonFuture.wait();
    Pokemon &chosenPokemon = chosenPokemonFuture.get();
    std::cout << "Go " << chosenPokemon.getNickname_() << "!" << std::endl
              << std::endl;
    BattleCry bc;
    bc.add(std::bind(&Pokemon::battleCry, pokemon));
    bc.add(std::bind(&Pokemon::battleCry, chosenPokemon));
    bc();
    std::cout << std::endl;
    while (!battleFinished)
    {
      std::cout << pokemon->getName_() << ": " << pokemon->getHealth_() << " HP" << std::endl
                << std::endl;
      std::cout << chosenPokemon.getNickname_() << ": " << chosenPokemon.getHealth_() << " HP" << std::endl
                << std::endl;
      std::future<PlayerBattleChoice> choiceFuture = player->makeBattleChoice();
      // Could do something else while waiting for player choice
      choiceFuture.wait();
      PlayerBattleChoice choice = choiceFuture.get();
      try
      {
        switch (choice)
        {
        case PlayerBattleChoice::Attack:
        {
          std::cout << "Attacking wild pokemon" << std::endl
                    << std::endl;
          Attack<Pokemon> attack(chosenPokemon);
          std::cout << attack.doAttack(*pokemon) << std::endl;
          break;
        }
        case PlayerBattleChoice::UseItem:
        {
          std::shared_ptr<PokeBagItem> potion = player->choosePokeBagItem(PlayerBattleChoice::UseItem);
          potion->Use(chosenPokemon, [](PokeBagItemResult res) {
            std::cout << "res.result: " << res.result << std::endl;
          });
          break;
        }
        case PlayerBattleChoice::UsePokeball:
        {
          std::shared_ptr<PokeBagItem> pokeball = player->choosePokeBagItem(PlayerBattleChoice::UsePokeball);
          pokeball->Use(*pokemon, [pokemon, player](PokeBagItemResult res) {
            if (res.result == "You caught the Pokemon\n")
            {
              std::cout << "You caught the wild " << pokemon->getName_()
                        << "! Give your new pokemon a nickname: " << std::endl;
              std::string nickname;
              std::cin >> nickname;
              pokemon->setNickname_(nickname);
              player->getBag().addPokemon(*pokemon);
            }
            else
            {
              std::cout << "The wild " << pokemon->getName_()
                        << " was not caught!" << std::endl;
            }
          });
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
      catch (const ChoiceCancelledException &e)
      {
        // std::cerr << e.what() << '\n';
      }
      catch (const NoPokeballsException &e)
      {
        std::cerr << e.what() << std::endl
                  << std::endl;
      }
      catch (const NoPotionsException &e)
      {
        std::cerr << e.what() << std::endl
                  << std::endl;
      }
    }
  } // namespace battle

} // namespace battle

#endif