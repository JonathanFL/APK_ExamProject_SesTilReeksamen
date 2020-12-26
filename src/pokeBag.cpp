#include "include/exceptions/cancel_exception.hpp"
#include "include/poke_center.hpp"
#include <algorithm>
#include <iterator>
#include <memory>
#include <numeric>
#include <variant>
#include <vector>
void PokeBag::empty() { std::cout << "Emptying bag..." << std::endl; }

// std::shared_ptr<PokeBagItem> &PokeBag::getItemByIndex(unsigned int index)
// {
//   if (this->items_.size() > index)
//     return this->items_.at(index);
//   else
//   {
//     return ;
//   }
// }

std::shared_ptr<PokeBagItem> PokeBag::getItemByName(std::string itemName)
{
  std::vector<shared_ptr<PokeBagItem>>::iterator it;
  it = find_if(items_.begin(), items_.end(),
               [itemName](std::shared_ptr<PokeBagItem> p) {
                 return p->getType() == itemName;
               });
  if (it == items_.end())
  {
    std::cout << "No Items with that name - try another one" << std::endl;
    return nullptr;
  }
  return *it;
}

void PokeBag::addItem(std::shared_ptr<PokeBagItem> item)
{
  this->items_.push_back(item);
}

void PokeBag::listItems()
{
  std::cout << "--- Items in PokeBag: ---\n";
  std::ostream_iterator<std::shared_ptr<PokeBagItem>> oStreamIter(std::cout,
                                                                  "\n");
  copy(items_.begin(), items_.end(),
       oStreamIter); // copy vil compile sålænge objektet har operator ++ = og *
}

void PokeBag::listNumberOfEachItemByType()
{
  int numberOfPokeBalls = count_if(
      items_.begin(), items_.end(), [](std::shared_ptr<PokeBagItem> p) {
        return p->getType() == PokeCenter::Items.at(0).first;
      });
  int numberOfGreatBalls = count_if(
      items_.begin(), items_.end(), [](std::shared_ptr<PokeBagItem> p) {
        return p->getType() == PokeCenter::Items.at(1).first;
      });
  int numberOfUltraBalls = count_if(
      items_.begin(), items_.end(), [](std::shared_ptr<PokeBagItem> p) {
        return p->getType() == PokeCenter::Items.at(2).first;
      });
  int numberOfMasterBalls = count_if(
      items_.begin(), items_.end(), [](std::shared_ptr<PokeBagItem> p) {
        return p->getType() == PokeCenter::Items.at(3).first;
      });
  int numberOfSuperPotion = count_if(
      items_.begin(), items_.end(), [](std::shared_ptr<PokeBagItem> p) {
        return p->getType() == PokeCenter::Items.at(3).first;
      });
  int numberOfHyperPotion = count_if(
      items_.begin(), items_.end(), [](std::shared_ptr<PokeBagItem> p) {
        return p->getType() == PokeCenter::Items.at(4).first;
      });
  if (numberOfPokeBalls > 0)
  {
    std::cout << numberOfPokeBalls << " Pokeball(s)\n";
  }
  if (numberOfGreatBalls > 0)
  {
    std::cout << numberOfGreatBalls << " Greatball(s)\n";
  }
  if (numberOfUltraBalls > 0)
  {
    std::cout << numberOfUltraBalls << " Ultraball(s)\n";
  }
  if (numberOfMasterBalls > 0)
  {
    std::cout << numberOfMasterBalls << " Ultraball(s)\n";
  }
  if (numberOfSuperPotion > 0)
  {
    std::cout << numberOfSuperPotion << " Superpotions(s)\n";
  }
  if (numberOfHyperPotion > 0)
  {
    std::cout << numberOfHyperPotion << " Hyperpotions(s)" << std::endl;
  }
}

double PokeBag::getTotalValue()
{
  std::vector<double> prices;
  std::transform(
      items_.begin(), items_.end(), std::back_inserter(prices),
      [](std::shared_ptr<PokeBagItem> item) { return item->getPrice(); });
  return std::accumulate(prices.begin(), prices.end(), 0.0);
  return 0;
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
  if (it == pokemons_.end()) return nullptr;
  return &*it;
}
