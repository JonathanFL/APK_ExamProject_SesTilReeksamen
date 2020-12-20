#include <iostream>
#include <map>
#include <string>
#include "../pokemon/poke_type.hpp"

using namespace poketypes;

namespace factories
{
    static PokemonTypeInstance getPokemonType(std::string type)
    {
        if (type == "ElectricPokemonType")
        {
            return ElectricPokemonType();
        }
        else if (type == "WaterPokemonType")
        {
            return WaterPokemonType();
        }
        else
        {
            return WaterPokemonType();
        }
    };
} // namespace factories
