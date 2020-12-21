#include "include/poke_bag/pokeBag.hpp"
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <memory>
void PokeBag::empty() { std::cout << "Emptying bag..." << std::endl; }

std::variant<PokeBagItem*, ErrorCode> PokeBag::getItemByIndex(unsigned int index) // no-throw-guarantee
{
  if(this->items_.size() > index)
    return this->items_.at(index);
  else
    return ErrorCode::SystemError;
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

