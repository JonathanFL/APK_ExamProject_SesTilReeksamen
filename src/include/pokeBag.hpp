#ifndef POKEBAG_HPP
#define POKEBAG_HPP
#include "pokeBagItem.hpp"
#include "pokemon.hpp"
#include <vector>
class PokeBag
{
private:
  std::vector<PokeBagItem> items_;
  std::vector<IPokemon>    pokemons_;

public:
  void empty();

  void addItem(PokeBagItem&& item);

  double getTotalValue();

//   void sortPokemon(auto comparer) {}
};

#endif