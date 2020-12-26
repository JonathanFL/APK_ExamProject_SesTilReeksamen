#ifndef __POKE_CENTER_H__
#define __POKE_CENTER_H__

#include "include/poke_center.hpp"
namespace PokeCenter
{
void Center::heal(Pokemon &pokemon)
{
  pokemon.setHealth_(pokemon.getMaxHealth_());
}

void Center::usePokecenter(Player &p)
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
  std::cout << "Make choice >";
  std::string input;
  std::cin >> input;
  Utilities::clearScreen();
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
  catch (const std::invalid_argument &e)
  {
    std::cout << "Invalid input"
              << "\n";
  }
  catch (const std::out_of_range &e)
  {
    std::cout << "Input number was out of range" << e.what() << "\n";
  }
}

void Center::buyPokeBagItem(PokeBag &playerBag)
{
  while (1)
  {
    Utilities::clearScreen();
    std::cout << "Available items are:"
              << "\n";
    listAvailableItems();
    std::cout << "What would you like to buy?"
              << "\n";
    std::cout << "Input name of Item or X to Quit >";
    std::string input;
    std::cin >> input;
    Utilities::clearScreen();
    Utilities::toLower(input);
    if (input == "x")
    {
      throw ChoiceCancelledException("Cancelled PokeCenter choice");
    }
    auto item = getPokeBagItem(input);
    if (item.index() == 0)
    {
      addToBag(playerBag,
               std::move(std::get<std::shared_ptr<PokeBagItem>>(item)));
    }
  }
}

std::variant<shared_ptr<PokeBagItem>, std::shared_ptr<std::nullptr_t>> &&
Center::getPokeBagItem(const std::string choice)
{
  std::vector<std::shared_ptr<PokeBagItem>>::iterator it =
      find_if(pokeBagItems_.begin(), pokeBagItems_.end(),
              [choice](std::shared_ptr<PokeBagItem> &p) {
                return p->getType() == choice;
              });
  if (it != pokeBagItems_.end())
  {
    return std::move(*it);
  }
  else
  {
    return std::make_shared<std::nullptr_t>(nullptr);
  }
}

void Center::addToBag(PokeBag &bag, std::shared_ptr<PokeBagItem> &&item)
{
  bag.addItem(std::forward<std::shared_ptr<PokeBagItem>>(item));
}
} // namespace PokeCenter
#endif // __POKE_CENTER_H__