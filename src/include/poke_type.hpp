#ifndef POKETYPE_HPP
#define POKETYPE_HPP
#include "element_type.hpp"
#include "type_list.hpp"
#include "type_list_algorithms.hpp"
#include <string>
namespace poketypes
{
template <typename T, typename STL, typename WTL, typename RTL, typename VTL>
class PokemonType
{
  static_assert(IsDerivedElementType<T>::value);
  static_assert(Every<WTL, IsDerivedElementType>::value);
  static_assert(Every<STL, IsDerivedElementType>::value);
  static_assert(Every<RTL, IsDerivedElementType>::value);
  static_assert(Every<VTL, IsDerivedElementType>::value);
  typedef WTL WeakAgainst;
  typedef STL StrongAgainst;
  typedef RTL ResistantAgainst;
  typedef VTL VulnerableAgainst;

public:
};
class FirePokemonType
    : public PokemonType<
          FireType, TYPELIST1(GrassType), TYPELIST2(WaterType, FireType),
          TYPELIST2(GrassType, FireType), TYPELIST2(GroundType, WaterType)>
{
};

class WaterPokemonType
    : public PokemonType<WaterType, TYPELIST2(GroundType, FireType),
                         TYPELIST2(WaterType, GrassType),
                         TYPELIST2(FireType, WaterType),
                         TYPELIST2(GrassType, ElectricType)>
{
};

class GroundPokemonType
    : public PokemonType<GroundType, TYPELIST2(FireType, ElectricType),
                         TYPELIST1(GrassType), TYPELIST1(ElectricType),
                         TYPELIST2(WaterType, GrassType)>
{
};

class GrassPokemonType
    : public PokemonType<GrassType, TYPELIST2(GroundType, WaterType),
                         TYPELIST2(FireType, GrassType),
                         TYPELIST4(GrassType, WaterType, GroundType,
                                   ElectricType),
                         TYPELIST1(FireType)>
{
};

class ElectricPokemonType
    : public PokemonType<ElectricType, TYPELIST1(WaterType),
                         TYPELIST3(GroundType, GrassType, ElectricType),
                         TYPELIST1(ElectricType), TYPELIST1(GroundType)>
{
};

typedef TYPELIST5(FirePokemonType, WaterPokemonType, GroundPokemonType,
                  GrassPokemonType, ElectricPokemonType) PokemonTypeList;
} // namespace poketypes
#endif