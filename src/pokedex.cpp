#include "include/pokemon/pokedex.hpp"
class PokedexPrinterVisitor : public boost::static_visitor<std::string>
{
public:
  std::string operator() (const std::string &s) const
  {
    return "Unkown pokémon: " + s;
  }

  std::string operator() (const Pokemon &p) const
  {
    return ""; // Skal måske laves om så den printer
  }
};

void Pokedex::print()
{
  for (const auto & [n,p]: pokemons_)
  {
    std::cout << "No. " << n << boost::apply_visitor(PokedexPrinterVisitor(), p) << std::endl;
  }
}

int Pokedex::discovered() { return 0; }

int Pokedex::undiscovered() { return pokemons_.size() - discovered(); }
