#ifndef POTION_HPP
#define POTION_HPP

#include "../pokeBagItem.hpp"
#include <iostream>

class Potion : public PokeBagItem
{
public:
  bool heal(Pokemon &pokemon, unsigned int amount)
  {
    auto pokemonHealth    = pokemon.getHealth_();
    auto pokemonMaxHealth = pokemon.getMaxHealth_();
    if (pokemonHealth + amount > pokemonMaxHealth)
    {
      pokemon.setHealth_(pokemonMaxHealth);
    }
    else
    {
      pokemon.setHealth_(pokemonHealth + amount);
    }
    return pokemon.getHealth_() == pokemon.getMaxHealth_() ||
           pokemon.getHealth_() == pokemonHealth + amount;
  }

  Potion() {}

  void Use(Pokemon &                                  pokemon,
           std::function<void(PokeBagItemResult res)> callback) override
  {
    UsePotion(pokemon, callback);
  }
  void format(std::ostream &out) const override { this->formatImpl(out); }

  virtual void formatImpl(std::ostream &out) const = 0;

  virtual void
  UsePotion(Pokemon &                                  pokemon,
            std::function<void(PokeBagItemResult res)> callback) = 0;

  virtual ~Potion();

private:
};

#endif