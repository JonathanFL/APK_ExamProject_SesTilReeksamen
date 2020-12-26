#include "include/poke_center.hpp"

void PokeCenter::Center::heal(Pokemon &pokemon)
{
  pokemon.setHealth_(pokemon.getMaxHealth_());
}

std::shared_ptr<PokeBagItem> &&PokeCenter::Center::buyPotion()
{
  while (1)
  {
    std::cout
        << "Enter the name of the Ball you would like to buy\nType X to exit";
    std::string choice;
    std::cin >> choice;
    Utilities::toLower(choice);
    if (choice == "x")
    {
      throw ChoiceCancledException("BuyPotion exit");
    }
    std::vector<std::shared_ptr<PokeBagItem>>::iterator it =
        find_if(potions_.begin(), potions_.end(),
                [choice](std::shared_ptr<PokeBagItem> &p) {
                  return p->getType() == choice;
                });
    if (it != potions_.end())
    {
      return std::move(*it);
    }
  }
}

std::shared_ptr<PokeBagItem> &&PokeCenter::Center::buyBall()
{
  while (1)
  {
    std::cout
        << "Enter the name of the Ball you would like to buy\nType X to exit";
    std::string choice;
    std::cin >> choice;
    Utilities::toLower(choice);
    if (choice == "x")
    {
      throw ChoiceCancledException("BuyPotion exit");
    }
    std::vector<std::shared_ptr<PokeBagItem>>::iterator it =
        find_if(balls_.begin(), balls_.end(),
                [choice](std::shared_ptr<PokeBagItem> &p) {
                  return p->getType() == choice;
                });
    if (it == balls_.end())
    {
      return std::move(*it);
    }
  }
}

void PokeCenter::Center::usePokecenter(Player &p)
{
  Utilities::clearScreen();
  std::cout << "Welcome to the pokecenter"
            << "\n";
  std::cout << "What would you like to do?"
            << "\n";
  std::cout << PokeCenter::PokecenterChoice::HealPokemon << ". Heal pokemon"
            << "\n";
  std::cout << PokeCenter::PokecenterChoice::BuyItem << ". Buy item"
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
      case PokeCenter::PokecenterChoice::HealPokemon:
      {
        PokeBag &playerBag = p.getBag();
        playerBag.forEachPokemon([&](Pokemon &p) { heal(p); });
        break;
      }

      case PokeCenter::PokecenterChoice::BuyItem:
      {
        PokeBag &playerBag = p.getBag();
        playerBag.addItem(std::move(buyPokeBagItem()));
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

std::shared_ptr<PokeBagItem> &&PokeCenter::Center::buyPokeBagItem()
{
  Utilities::clearScreen();
  std::cout << "What would you like to buy?"
            << "\n";
  std::cout << "Available items are:"
            << "\n";
  listAvailableItems();
  std::cout << PokeCenter::BuyItemChoice::BuyPokeball << ". Pokeball \n";
  std::cout << PokeCenter::BuyItemChoice::BuyPotion << ". Potion \n";
  std::cout << "Input choice >";
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
      case PokeCenter::BuyItemChoice::BuyPokeball:
        return buyBall();
        break;
      case PokeCenter::BuyItemChoice::BuyPotion:
        return buyPotion();
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
