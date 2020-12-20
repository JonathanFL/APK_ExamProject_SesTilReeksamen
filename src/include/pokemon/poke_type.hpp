#ifndef POKETYPE_HPP
#define POKETYPE_HPP
#include "../metaprogramming/type_list.hpp"
#include "../metaprogramming/type_list_algorithms.hpp"
#include "element_type.hpp"
#include <boost/variant.hpp>
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

public:
  typedef T                                                  Type;
  typedef WTL                                                WeakAgainst;
  typedef STL                                                StrongAgainst;
  typedef RTL                                                ResistantAgainst;
  typedef VTL                                                VulnerableAgainst;
  template <typename D, typename ORTL, typename OVTL> double getAttackModifier()
  {
    const bool strongAgainst     = Contains<STL, D>::value;
    const bool weakAgainst       = Contains<WTL, D>::value;
    const bool otherVulnerableTo = Contains<OVTL, T>::value;
    const bool otherResistantTo  = Contains<ORTL, T>::value;
    double     attackModifier    = 1;
    if constexpr (strongAgainst)
    {
      attackModifier *= 1.5;
    }
    if constexpr (weakAgainst)
    {
      attackModifier *= 0.666;
    }
    if constexpr (otherVulnerableTo)
    {
      attackModifier *= 1.5;
    }
    if constexpr (otherResistantTo)
    {
      attackModifier *= 0.666;
    }
    return attackModifier;
  }
};
struct FirePokemonType
    : public PokemonType<
          FireType, TYPELIST1(GrassType), TYPELIST2(WaterType, FireType),
          TYPELIST2(GrassType, FireType), TYPELIST2(GroundType, WaterType)>
{
  typedef FireType Type;
  typedef TYPELIST1(GrassType) StrongAgainst;
  typedef TYPELIST2(WaterType, FireType) WeakAgainst;
  typedef TYPELIST2(GrassType, FireType) ResistantAgainst;
  typedef TYPELIST2(GroundType, WaterType) VulnerableAgainst;
};

struct WaterPokemonType
    : public PokemonType<WaterType, TYPELIST2(GroundType, FireType),
                         TYPELIST2(WaterType, GrassType),
                         TYPELIST2(FireType, WaterType),
                         TYPELIST2(GrassType, ElectricType)>
{
  typedef WaterType Type;
  typedef TYPELIST2(GroundType, FireType) StrongAgainst;
  typedef TYPELIST2(WaterType, GrassType) WeakAgainst;
  typedef TYPELIST2(FireType, WaterType) ResistantAgainst;
  typedef TYPELIST2(GrassType, ElectricType) VulnerableAgainst;
};

struct GroundPokemonType
    : public PokemonType<GroundType, TYPELIST2(FireType, ElectricType),
                         TYPELIST1(GrassType), TYPELIST1(ElectricType),
                         TYPELIST2(WaterType, GrassType)>
{
  typedef GroundType Type;
  typedef TYPELIST2(ElectricType, FireType) StrongAgainst;
  typedef TYPELIST1(GrassType) WeakAgainst;
  typedef TYPELIST1(ElectricType) ResistantAgainst;
  typedef TYPELIST2(GrassType, WaterType) VulnerableAgainst;
};

struct GrassPokemonType
    : public PokemonType<GrassType, TYPELIST2(GroundType, WaterType),
                         TYPELIST2(FireType, GrassType),
                         TYPELIST4(GrassType, WaterType, GroundType,
                                   ElectricType),
                         TYPELIST1(FireType)>
{
  typedef GrassType Type;
  typedef TYPELIST2(GroundType, WaterType) StrongAgainst;
  typedef TYPELIST2(FireType, GrassType) WeakAgainst;
  typedef TYPELIST4(ElectricType, GrassType, WaterType,
                    GroundType) ResistantAgainst;
  typedef TYPELIST1(FireType) VulnerableAgainst;
};

struct ElectricPokemonType
    : public PokemonType<ElectricType, TYPELIST1(WaterType),
                         TYPELIST3(GroundType, GrassType, ElectricType),
                         TYPELIST1(ElectricType), TYPELIST1(GroundType)>
{
  typedef ElectricType Type;
  typedef TYPELIST1(WaterType) StrongAgainst;
  typedef TYPELIST3(GroundType, GrassType, ElectricType) WeakAgainst;
  typedef TYPELIST1(ElectricType) ResistantAgainst;
  typedef TYPELIST1(GroundType) VulnerableAgainst;
};

struct NormalPokemonType
    : public PokemonType<NormalType, TYPELIST1(NullType), TYPELIST1(NullType),
                         TYPELIST1(NullType), TYPELIST1(NullType)>
{
  typedef NormalType Type;
  typedef TYPELIST1(NullType) StrongAgainst;
  typedef TYPELIST1(NullType) WeakAgainst;
  typedef TYPELIST1(NullType) ResistantAgainst;
  typedef TYPELIST1(NullType) VulnerableAgainst;
};

typedef boost::variant<NormalPokemonType, FirePokemonType, WaterPokemonType,
                       GroundPokemonType, GrassPokemonType, ElectricPokemonType>
    PokemonTypeVariant;

struct PokemonTypeModifierVisitor : public boost::static_visitor<double>
{
  template <typename T, typename U> double operator()(T &t, U &u) const
  {
    return t.getAttackModifier<typename decltype(U::Type),
                               typename U::ResistantAgainst(),
                               typename U::VulnerableAgainst()>();
  }
  // double operator()(WaterPokemonType &pokemon) const {

  // }

  // double operator()(GroundPokemonType &pokemon) const {

  // }

  // double operator()(GrassPokemonType &pokemon) const {

  // }

  // double operator()(ElectricPokemonType &pokemon) const {

  // }
};

typedef TYPELIST5(FirePokemonType, WaterPokemonType, GroundPokemonType,
                  GrassPokemonType, ElectricPokemonType) PokemonTypeList;
} // namespace poketypes
// namespace poketypes
#endif