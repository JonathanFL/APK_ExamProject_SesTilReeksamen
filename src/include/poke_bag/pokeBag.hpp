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

  template <typename P, typename... Pokemons>
  void addPokemon(P & pokemon, Pokemons&... pokemons) 
  {
    static_assert(IsSame<P, Pokemon>::value);
    addPokemon(pokemon);
    addPokemon(pokemons...);
  }

  void addPokemon(Pokemon & pokemon) {
    pokemons_.push_back(std::move(pokemon));
  }

  double getTotalValue();
  void listPokemon();
  Pokemon * findPokemon(std::string name);
  const std::vector<Pokemon> & getPokemon() const {
    return pokemons_;
  }
  
//   void sortPokemon(auto comparer) {}
};

#endif