#ifndef __POKE_CENTER_H__
#define __POKE_CENTER_H__

#include "include/poke_center.hpp"
namespace PokeCenter
{
void Center::heal(Pokemon &pokemon)
{
  std::cout << "Healing pokemon: " << pokemon.getNickname_() << std::endl;
  pokemon.setHealth_(pokemon.getMaxHealth_());
}

void Center::usePokecenter(game::Player &p)
{
  while (1)
  {
    Utilities::clearScreen();
    std::cout << "Welcome to the pokecenter"
              << "\n";
    std::cout << "What would you like to do?"
              << "\n";
    std::cout << PokecenterChoice::HealPokemon << ". Heal pokemon"
              << "\n";
    std::cout << PokecenterChoice::BuyItem << ". Buy item"
              << "\n";
    std::cout << "Press x and enter to go back"
              << "\n";
    std::cout << "Make choice >";
    std::string input;
    std::cin >> input;
    Utilities::clearScreen();
    Utilities::toLower(input);
    if (input == "x")
    {
      return;
    }
    try
    {
      int chosenNumber = std::stoi(input);
      if (chosenNumber > 0 && chosenNumber < 3)
      {
        switch (chosenNumber)
        {
        case PokecenterChoice::HealPokemon:
        {
          PokeBag &playerBag = p.getBag();
          playerBag.forEachPokemon([&](Pokemon &p) { heal(p); });
          break;
        }

        case PokecenterChoice::BuyItem:
        {
          PokeBag &playerBag = p.getBag();
          buyPokeBagItem(playerBag);
          break;
        }
        }
      }
      else
      {
        throw std::out_of_range("Must be either 1 or 2");
      }
    }
    catch (const std::out_of_range &e)
    {
      std::cout << "Input number was out of range" << e.what() << "\n";
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << e.what() << "\n";
    }
  }
}

void Center::buyPokeBagItem(PokeBag &playerBag)
{
  Utilities::clearScreen();
  while (1)
  {
    std::cout << "Available items are:"
              << "\n";
    listAvailableItems();
    std::cout << "What would you like to buy?"
              << "\n";
    std::cout << "Input name of Item - 'X' to go back >";
    std::string input;
    std::cin >> input;
    Utilities::toLower(input);
    if (input == "x")
    {
      Utilities::clearScreen();
      return;
    }
    auto indexToRemoveAt = -1;
    auto item            = getPokeBagItem(input, indexToRemoveAt);
    Utilities::clearScreen();
    if (item)
    {
      std::cout << "Added " << pokeBagItems_.at(indexToRemoveAt)->getType()
                << " to bag" << std::endl
                << std::endl;
      playerBag.addItem(std::move(item));
      pokeBagItems_.erase(pokeBagItems_.begin() + indexToRemoveAt);
    }
    else
    {
      std::cout << "Unknown item. Please enter the name of an item on the list "
                << std::endl
                << std::endl;
    }
  }
}

shared_ptr<PokeBagItem> Center::getPokeBagItem(const std::string choice,
                                               int &indexToRemoveAt)
{
  std::vector<std::shared_ptr<PokeBagItem>>::iterator it =
      find_if(pokeBagItems_.begin(), pokeBagItems_.end(),
              [choice, &indexToRemoveAt](std::shared_ptr<PokeBagItem> &p) {
                auto type = p->getType();
                Utilities::toLower(type);
                ++indexToRemoveAt;
                return type == choice;
              });
  if (it == pokeBagItems_.end()) return nullptr;
  return *it;
}
} // namespace PokeCenter
#endif // __POKE_CENTER_H__