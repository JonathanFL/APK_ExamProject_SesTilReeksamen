#ifndef POKETYPEFACTORY_HPP
#define POKETYPEFACTORY_HPP

#include <iostream>
#include <map>
#include "poke_type.hpp"
#include "../exceptions/UnknownPokemonTypeException.hpp"

namespace poketypes
{
    class PokeTypeFactory
    {
    private:
        std::map<std::string, PokemonTypeVariant> pokeTypeMap;

    public:
        PokeTypeFactory()
        {
            pokeTypeMap["ElectricPokemonType"] = ElectricPokemonType();
            pokeTypeMap["WaterPokemonType"] = WaterPokemonType();
            pokeTypeMap["FirePokemonType"] = FirePokemonType();
            pokeTypeMap["GroundPokemonType"] = GroundPokemonType();
            pokeTypeMap["GrassPokemonType"] = GrassPokemonType();
            pokeTypeMap["NormalPokemonType"] = NormalPokemonType();
        };
        PokemonTypeVariant getPokeTypeFromString(const std::string type)
        {
            if (pokeTypeMap.count(type))
            {
                return pokeTypeMap[type];
            }

            throw(exceptions::UnknownPokemonTypeException(type));
        }
    };

} // namespace poketypes

#endif