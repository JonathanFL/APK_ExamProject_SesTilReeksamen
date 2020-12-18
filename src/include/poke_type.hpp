#ifndef POKETYPE_HPP
#define POKETYPE_HPP
#include "element_type.hpp"
#include "type_list.hpp"
#include <string>
namespace poketypes
{
template <typename T, typename WTL, typename STL,
          typename = std::enable_if<std::is_base_of<ElementType, T>::value>>
class PokemonType
{
};

class FirePokemonType
    : public PokemonType<FireType, TypeList<WaterType, NullType>,
                         TypeList<GrassType, NullType>>
{
};

class WaterPokemonType
    : public PokemonType<WaterType, TypeList<GrassType, ElectricType>,
                         TypeList<FireType, GroundType>>
{
};

class GroundPokemonType
    : public PokemonType<GroundType, TypeList<WaterType, GrassType>,
                         TypeList<ElectricType, NullType>>
{
};

class GrassPokemonType
    : public PokemonType<GrassType, TypeList<FireType, NullType>,
                         TypeList<WaterType, GroundType>>
{
};

class ElectricPokemonType
    : public PokemonType<ElectricType, TypeList<GroundType, GrassType>,
                         TypeList<WaterType, NullType>>
{
};

typedef TYPELIST5(FirePokemonType, WaterPokemonType, GroundPokemonType,
                  GrassPokemonType, ElectricPokemonType) PokemonTypeList;
} // namespace poketypes
#endif