#ifndef POKETYPEFACTORY_HPP
#define POKETYPEFACTORY_HPP

#include <iostream>
#include "poke_type.hpp"

namespace poketypes
{
    class PokeTypeFactory
    {
    private:
        /* data */
    public:
        PokeTypeFactory(){};
        static PokemonTypeVariant getPokeTypeFromString(std::string type)
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
                return ElectricPokemonType();
            }
        }
    };

} // namespace poketypes

#endif