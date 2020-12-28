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
  std::vector<std::shared_ptr<PokeBagItem>>
      items_; // For polymorfi, skal bruge pointers!
              // Hvis ikke pointers, kan compileren kun se den abstracte klasse
  PokemonList pokemons_;

public:

  void addItem(std::shared_ptr<PokeBagItem> &&item);

  std::shared_ptr<PokeBagItem>  getItemByName(std::string itemName,
                                              int &       indexToRemoveAt);
  void                          removeItemFromBag(const int indexToRemoveAt);
  void                          listItems();
  void                          listNumberOfEachPokeItem();
  bool                          listNumberOfEachPokeBall();
  bool                          listNumberOfEachPotion();

  template <typename P, typename... Pokemons>
  void addPokemon(P &pokemon, Pokemons &... pokemons)
  {
    static_assert(IsSame<P, Pokemon>::value);
    addPokemon(pokemon);
    addPokemon(pokemons...);
  }

  void addPokemon(Pokemon &pokemon) { pokemons_.push_back(std::move(pokemon)); }

  void addPokemons(PokemonList &&pokemons);

  double                      getTotalValue();
  void                        listBattleReadyPokemons();
  void                        listPokemon();
  Pokemon *                   findPokemon(std::string name);
  const std::vector<Pokemon> &getPokemon() const { return pokemons_; }
  void                        forEachPokemon(std::function<void(Pokemon &)> f)
  {
    std::for_each(pokemons_.begin(), pokemons_.end(), f);
  }

  //   void sortPokemon(auto comparer) {}
};

#endif