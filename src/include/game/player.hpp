#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "../metaprogramming/if_then_else.hpp"
#include "../poke_bag/pokeBag.hpp"
#include "../threading/create_thread.hpp"
// #include "../pokemon/pokedex.hpp"
#include <future>
#include <string>
enum class PlayerBattleChoice : unsigned int
{
  Attack      = 1,
  UseItem     = 2,
  UsePokeball = 3,
  Run         = 4,
  Nothing     = 5,
};

class Player
{
private:
  std::string name_;
  PokeBag     bag_;
  // Pokedex     pokedex_;

public:
  Player(std::string &&name, PokeBag &pokeBag)
      : name_(std::move(name)), bag_(std::move(pokeBag))
  {
  }

  PokeBagItem* choosePokeBagItem()
  {
    std::cout << "Enter the name of the Poke Ball that you would like to choose:"
              << std::endl;
    bag_.listNumberOfEachItemByType();
    int choice;
    std::cin >> choice;
    return bag_.getItemByIndex(choice);
  }

  void     listPokemon() { bag_.listPokemon(); }
  Pokemon &choosePokemon()
  {
    std::cout << "Enter the name of the pokemon that you would like to choose:"
              << std::endl;
    bag_.listPokemon();
    std::string choice;
    std::cin >> choice;
    return *bag_.findPokemon(choice);
  }

  bool canBattle()
  {
    const PokemonList &pokemons = bag_.getPokemon();
    return !pokemons.empty() &&
           std::all_of(pokemons.begin(), pokemons.end(),
                        [](const Pokemon &p) { return p.getHealth_() > 0; });
  }

  std::future<PlayerBattleChoice> makeChoice()
  {
    auto choiceLambda = [](std::promise<PlayerBattleChoice> &&p) {
      bool               chosen = false;
      PlayerBattleChoice choice;
      while (!chosen)
      {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << static_cast<int>(PlayerBattleChoice::Attack) << ". Attack"
                  << std::endl;
        std::cout << static_cast<int>(PlayerBattleChoice::UseItem)
                  << ". Use item from bag" << std::endl;
        std::cout << static_cast<int>(PlayerBattleChoice::UsePokeball)
                  << ". Use pokeball" << std::endl;
        std::cout << static_cast<int>(PlayerBattleChoice::Run) << ". Run"
                  << std::endl;
        std::string input;
        std::cin >> input;
        int chosenNumber = std::stoi(input);
        if (chosenNumber > 0 && chosenNumber < 5)
        {
          chosen = true;
          switch (chosenNumber)
          {
          case 1:
            choice = PlayerBattleChoice::Attack;
            break;
          case 2:
            choice = PlayerBattleChoice::UseItem;
            break;
          case 3:
            choice = PlayerBattleChoice::UsePokeball;
            break;
          case 4:
            choice = PlayerBattleChoice::Run;
            break;
          }
        }
        else
        {
          std::cout << "Invalid choice - please choose again" << std::endl;
        }
      }
      p.set_value_at_thread_exit(choice);
    };
    return createFuture<PlayerBattleChoice>(choiceLambda);
  }
};

#endif