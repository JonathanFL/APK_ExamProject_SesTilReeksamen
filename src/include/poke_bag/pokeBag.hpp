#ifndef POKEBAG_HPP
#define POKEBAG_HPP
#include "../pokemon/pokemon.hpp"
#include "pokeBagItem.hpp"
#include <functional>
#include <memory>
#include <variant>
#include <vector>

enum class ErrorCode
{
  SystemError,
  IoError,
  NetworkError
};

class PokeBag
{
private:
  std::vector<std::shared_ptr<PokeBagItem>> items_; // For polymorfi, skal bruge pointers!
                                    // Hvis ikke pointers, kan compileren kun se den abstracte klasse
  std::vector<Pokemon>    pokemons_;

public:
  void empty();

  void addItem(std::shared_ptr<PokeBagItem> item);

  std::shared_ptr<PokeBagItem>& getItemByIndex(unsigned int index);
  std::shared_ptr<PokeBagItem> findPokeBagItem(std::string itemName);
  void listItems();
  void listNumberOfEachItemByType();

  template <typename P, typename... Pokemons>
  void addPokemon(P &pokemon, Pokemons &... pokemons)
  {
    static_assert(IsSame<P, Pokemon>::value);
    addPokemon(pokemon);
    addPokemon(pokemons...);
  }

  void addPokemon(Pokemon &pokemon) { pokemons_.push_back(std::move(pokemon)); }

  double getTotalValue();
  void listPokemon();
  Pokemon * findPokemon(std::string name);
  const std::vector<Pokemon> & getPokemon() const {
    return pokemons_;
  }
  void forEachPokemon(std::function<void(Pokemon &)> f) 
  {
    std::for_each(pokemons_.begin(), pokemons_.end(), f);
  }
  
//   void sortPokemon(auto comparer) {}
};

#endif