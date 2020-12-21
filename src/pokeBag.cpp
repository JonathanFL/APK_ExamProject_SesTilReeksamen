#include "include/poke_bag/pokeBag.hpp"
#include <algorithm>
#include <iterator>
#include <memory>
#include <numeric>
#include <vector>
void PokeBag::empty() { std::cout << "Emptying bag..." << std::endl; }

std::variant<PokeBagItem*, ErrorCode> PokeBag::getItemByIndex(unsigned int index) 
{
  try
  {
    return this->items_.at(index);
  }
  catch(const std::exception& e)
  {
    //std::cerr << "Index out of range - " << e.what() << "\n";
    return ErrorCode::SystemError;
  }
}

// void PokeBag::useItem(std::function<void()> callback) 
// {
//   std::cout << "Using item" << std::endl;
//   callback();
// }

void PokeBag::listItems(){
  std::ostream_iterator<PokeBagItem*> oStreamIter(std::cout, "\n");
  copy(items_.begin(), items_.end(), oStreamIter);// copy vil compile sålænge objektet har operator ++ = og *
}

double PokeBag::getTotalValue()
{
  // std::vector<double> prices;
  // std::transform(items_.begin(), items_.end(), std::back_inserter(prices),
  //                [](PokeBagItem &item) { return item.getPrice(); });
  // return std::accumulate(prices.begin(), prices.end(), 0.0);
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
      find_if(pokemons_.begin(), pokemons_.end(),
              [nickName](const Pokemon &p) { return p.getNickname_() == nickName; });
  if(it == pokemons_.end())
    return nullptr;
  return &*it;
}
