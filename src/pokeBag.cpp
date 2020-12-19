#include "include/pokeBag.hpp"
#include <algorithm>
#include <numeric>
#include <vector>
void PokeBag::empty() { std::cout << "Emptying bag..." << std::endl; }

void PokeBag::addItem(PokeBagItem &&item) {}

double PokeBag::getTotalValue()
{
  std::vector<double> prices;
  std::transform(items_.begin(), items_.end(), std::back_inserter(prices),
                 [](PokeBagItem item) { return item.getPrice(); });
  return std::accumulate(prices.begin(), prices.end(), 0.0);
}