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

  template<typename T>
  void addItem(PokeBagItem* item) {
    static_assert(std::is_base_of<PokeBagItem, T>::value, "The type must be a base class of `PokeBagItem`");
    static_assert(std::is_convertible<T&, PokeBagItem&>::value, "The type must be an *accessible* base class of `PokeBagItem`");
    this->items_.push_back(item);
  }
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

  // void useItem(std::function<void()> callback);
  std::variant<PokeBagItem*, ErrorCode> getItemByIndex(unsigned int index);

  void listItems();

  double getTotalValue();
  void listPokemon();
  Pokemon * findPokemon(std::string name);
  
//   void sortPokemon(auto comparer) {}
};

#endif