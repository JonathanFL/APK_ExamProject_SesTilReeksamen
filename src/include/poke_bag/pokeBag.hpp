#ifndef POKEBAG_HPP
#define POKEBAG_HPP
#include "pokeBagItem.hpp"
#include "../pokemon/pokemon.hpp"
#include <vector>
#include <memory>
#include <functional>
#include <variant>

enum class ErrorCode
{
    SystemError,
    IoError,
    NetworkError
};

class PokeBag
{
private:
  std::vector<PokeBagItem*> items_; // For polymorfi, skal bruge pointers!
                                    // Hvis ikke pointers, kan compileren kun se den abstracte klasse
  std::vector<Pokemon>    pokemons_;

public:
  void empty();

  void addItem(PokeBagItem* item);

  PokeBagItem* getItemByIndex(unsigned int index);
  PokeBagItem* findPokeBagItem(std::string itemName);

  void listItems();
  void listNumberOfEachItemByType();

  double getTotalValue();
  void listPokemon();
  Pokemon * findPokemon(std::string name);
  
//   void sortPokemon(auto comparer) {}
};

#endif