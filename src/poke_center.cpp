#include "include/poke_center.hpp"
#include "include/output/clear_screen.hpp"
#include "poke_bag/pokeBag.hpp"

void PokeCenter::Center::Heal(Pokemon &pokemon)
{
  pokemon.setHealth_(pokemon.getMaxHealth_());
}

std::shared_ptr<PokeBagItem> &&PokeCenter::Center::BuyPotion()
{
  std::cout << "Enter the name of the Potion you would like to buy\n";
  std::string choice;
  std::cin >> choice;
  std::vector<std::shared_ptr<PokeBagItem>>::iterator it =
      find_if(potions_.begin(), potions_.end(),
              [choice](std::shared_ptr<PokeBagItem> &p) {
                return p->getType() == choice;
              });
  if (it == potions_.end())
  {
    return std::make_shared(nullptr);
  }
  return std::move(*it);
}

std::shared_ptr<PokeBagItem> &&PokeCenter::Center::BuyBall()
{
    //TODO Handle incorrect choice or exit
  std::cout << "Enter the name of the Poke ball you would like to buy\n";
  std::string choice;
  std::cin >> choice;
  std::vector<std::shared_ptr<PokeBagItem>>::iterator it = find_if(
      balls_.begin(), balls_.end(), [choice](std::shared_ptr<PokeBagItem> &p) {
        return p->getType() == choice;
      });
  if (it == balls_.end())
  {
    return std::make_shared(nullptr);
  }
  return std::move(*it);
}

void PokeCenter::Center::usePokecenter(Player &p)
{
  clearScreen();
  std::cout << "Welcome to the pokecenter"
            << "\n";
  std::cout << "What would you like to do?"
            << "\n";
  std::cout << PokeCenter::PokeCenterChoice::HealPokemon << ". Heal pokemon"
            << "\n";
  std::cout << PokeCenter::PokeCenterChoice::BuyItem << ". Buy item"
            << "\n";
  std::cout << "Make choice >";
  std::string input;
  std::cin >> input;
  clearScreen();
  try
  {
    int chosenNumber = std::stoi(input);
    if (chosenNumber > 0 && chosenNumber < 3)
    {
      chosen = true;
      switch (chosenNumber)
      {
      case PokeCenter::PokeCenterChoice::HealPokemon:
        PokeBag &playerBag = p.getBag();
        playerBag.forEachPokemon(Heal);
        break;
      case PokeCenter::PokeCenterChoice::BuyItem:
        std::shared_ptr<PokeBagItem> item = buyPokeBagItem();
        PokeBag & playerBag = p.getBag();
        playerBag.addItem(std::move(item));
        break;
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

std::shared_ptr<PokeBagItem>&& PokeCenter::Center::buyPokeBagItem()
{
  clearScreen();
  std::cout << "What would you like to buy?"
            << "\n";
  std::cout << "Available items are:"
            << "\n";
  ListAvailableItems();
  std::cout << PokeCenter::BuyItemChoice::BuyPokeball << ". Pokeball \n";
  std::cout << PokeCenter::BuyItemChoice::BuyPotion << ". Potion \n";
  std::cout << "Input choice >";
  std::string input;
  std::cin >> input;
  clearScreen();
  try
  {
    int chosenNumber = std::stoi(input);
    if (chosenNumber > 0 && chosenNumber < 3)
    {
      chosen = true;
      switch (chosenNumber)
      {
      case PokeCenter::BuyItemChoice::BuyPokeball:
        return BuyBall();
        break;
      case PokeCenter::BuyItemChoiuce::BuyPotion:
        return BuyPotion();
        break;
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
