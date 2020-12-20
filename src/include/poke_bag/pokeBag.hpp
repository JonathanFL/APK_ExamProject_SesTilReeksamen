#ifndef POKEBAG_HPP
#define POKEBAG_HPP
#include "pokeBagItem.hpp"
#include "../pokemon/pokemon.hpp"
#include <vector>
#include <memory>
class PokeBag
{
private:
  std::vector<PokeBagItem*> items_; // For polymorfi, skal bruge pointers!
                                    // Hvis ikke pointers, kan compileren kun se den abstracte klasse
  std::vector<Pokemon>    pokemons_;

public:
  void empty();

  template<typename T, typename ...Args>
  void addItem(PokeBagItem* item) {
    static_assert(std::is_base_of<PokeBagItem, T>::value, "The type must be a base class of `PokeBagItem`");
    static_assert(std::is_convertible<T&, PokeBagItem&>::value, "The type must be an *accessible* base class of `PokeBagItem`");
    //std::cout << *item << std::endl;
    this->items_.push_back(item);
  }

  void listItems();

  double getTotalValue();
  
//   void sortPokemon(auto comparer) {}
};

#endif