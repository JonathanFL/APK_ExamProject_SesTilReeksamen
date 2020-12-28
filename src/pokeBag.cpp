#include "include/exceptions/UnknownPokemonException.hpp"
#include "include/exceptions/cancel_exception.hpp"
#include "include/poke_center.hpp"
#include <algorithm>
#include <iterator>
#include <memory>
#include <numeric>
#include <variant>
#include <vector>

std::shared_ptr<PokeBagItem> PokeBag::getItemByName(std::string itemName,
                                                    int &       indexToRemoveAt)
{
  std::vector<shared_ptr<PokeBagItem>>::iterator it;
  it = find_if(items_.begin(), items_.end(),
               [itemName, &indexToRemoveAt](std::shared_ptr<PokeBagItem> p) {
                 ++indexToRemoveAt;
                 auto itemType = p->getType();
                 Utilities::toLower(itemType);
                 return itemType == itemName;
               });
  if (it == items_.end())
  {
    Utilities::clearScreen();
    std::cout << "No Items with that name - try another one" << std::endl
              << std::endl;
    return nullptr;
  }
  return *it;
}

void PokeBag::removeItemFromBag(const int indexToRemoveAt)
{
  if (indexToRemoveAt > -1)
  {
    items_.erase(items_.begin() + indexToRemoveAt);
  }
}

void PokeBag::addItem(std::shared_ptr<PokeBagItem> &&item)
{
  this->items_.push_back(std::forward<std::shared_ptr<PokeBagItem>>(item));
}

void PokeBag::listItems()
{
  std::cout << "--- Items in PokeBag: ---\n";
  std::ostream_iterator<std::shared_ptr<PokeBagItem>> oStreamIter(std::cout,
                                                                  "\n");
  copy(items_.begin(), items_.end(),
       oStreamIter); // copy vil compile sålænge objektet har operator ++ = og *
}

void PokeBag::listNumberOfEachPokeItem()
{
  int numberOfBalls[PokeCenter::PokeCenterTypes::HyperpotionType + 1] = {};
  for (size_t i = 0; i < PokeCenter::PokeCenterTypes::HyperpotionType + 1; i++)
  {
    numberOfBalls[i] = count_if(
        items_.begin(), items_.end(), [i](std::shared_ptr<PokeBagItem> p) {
          return p->getType() == PokeCenter::Items.at(i).first;
        });
    if (numberOfBalls[i] > 0)
    {
      std::cout << numberOfBalls[i] << " " << PokeCenter::Items.at(i).first
                << "(s)\n";
    }
  }
}

bool PokeBag::listNumberOfEachPokeBall()
{
  bool hasPokeballs                                                    = false;
  int  numberOfBalls[PokeCenter::PokeCenterTypes::HyperpotionType - 1] = {};
  for (size_t i = 0; i < PokeCenter::PokeCenterTypes::HyperpotionType - 1; i++)
  {
    numberOfBalls[i] = count_if(
        items_.begin(), items_.end(), [i](std::shared_ptr<PokeBagItem> p) {
          return p->getType() == PokeCenter::Items.at(i).first;
        });
    if (numberOfBalls[i] > 0)
    {
      hasPokeballs = true;
      std::cout << numberOfBalls[i] << " " << PokeCenter::Items.at(i).first
                << "(s)\n";
    }
  }

  return hasPokeballs;
}

bool PokeBag::listNumberOfEachPotion()
{
  bool hasPotions       = false;
  int  numberOfBalls[2] = {};
  for (size_t i = 4; i < 6; i++)
  {
    numberOfBalls[i] = count_if(
        items_.begin(), items_.end(), [i](std::shared_ptr<PokeBagItem> p) {
          return p->getType() == PokeCenter::Items.at(i).first;
        });
    if (numberOfBalls[i] > 0)
    {
      hasPotions = true;
      std::cout << numberOfBalls[i] << " " << PokeCenter::Items.at(i).first
                << "(s)\n";
    }
  }
  return hasPotions;
}

double PokeBag::getTotalValue()
{
  std::vector<double> prices;
  std::transform(
      items_.begin(), items_.end(), std::back_inserter(prices),
      [](std::shared_ptr<PokeBagItem> item) { return item->getPrice(); });
  return std::accumulate(prices.begin(), prices.end(), 0.0);
}

void PokeBag::listBattleReadyPokemons()
{
  PokemonList nonFaintedPokemons;

  std::copy_if(pokemons_.begin(), pokemons_.end(),
               std::back_inserter(nonFaintedPokemons),
               [](Pokemon p) { return p.getHealth_() > 0; });

  std::ostream_iterator<Pokemon> oStreamIter(std::cout, "\n");
  copy(nonFaintedPokemons.begin(), nonFaintedPokemons.end(), oStreamIter);
}

void PokeBag::listPokemon()
{
  std::ostream_iterator<Pokemon> oStreamIter(std::cout, "\n");
  copy(pokemons_.begin(), pokemons_.end(), oStreamIter);
}

Pokemon *PokeBag::findPokemon(std::string nickName)
{
  std::vector<Pokemon>::iterator it =
      find_if(pokemons_.begin(), pokemons_.end(), [nickName](const Pokemon &p) {
        return p.getNickname_() == nickName;
      });
  if (it == pokemons_.end()) throw UnknownPokemonException();
  return &*it;
}

void PokeBag::addPokemons(PokemonList &&pokemons)
{
  pokemons_ = std::move(pokemons);
}
