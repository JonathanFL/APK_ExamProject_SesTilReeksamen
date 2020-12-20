#ifndef ELEMENTTYPE_HPP
#define ELEMENTTYPE_HPP
#include <type_traits>
class ElementType
{
};

class FireType : public ElementType
{
};

class WaterType : public ElementType
{
};

class GroundType : public ElementType
{
};

class GrassType : public ElementType
{
};

class ElectricType : public ElementType
{
};

class NormalType : public ElementType 
{

};

template <typename T> 
struct IsDerivedElementType {
    static const bool value = std::is_base_of<ElementType, T>::value || IsSame<T, NullType>::value;
};

template <typename T> struct ElementTypeTraits
{
  //   static_assert(IsDerivedElementType<T>::value);
  //   static_assert(Every<WTL, IsDerivedElementType>::value);
  //   static_assert(Every<STL, IsDerivedElementType>::value);
  //   static_assert(Every<RTL, IsDerivedElementType>::value);
  //   static_assert(Every<VTL, IsDerivedElementType>::value);

public:
  //   typedef WTL WeakAgainst;
  //   typedef STL StrongAgainst;
  //   typedef RTL ResistantAgainst;
  //   typedef VTL VulnerableAgainst;
  //   template<typename D, typename ORTL, typename OVTL>
  //   double constexpr getAttackModifier() {
  //       const bool strongAgainst = Contains<STL, D>::value;
  //       const bool weakAgainst = Contains<WTL, D>::value;
  //       const bool otherVulnerableTo = Contains<OVTL, T>::value;
  //       const bool otherResistantTo = Contains<ORTL, T>::value;
  //       double attackModifier = 1;
  //       if constexpr(strongAgainst) {
  //           attackModifier *= 1.5;
  //       }
  //       if constexpr(weakAgainst) {
  //           attackModifier *= 0.666;
  //       }
  //       if constexpr(otherVulnerableTo) {
  //           attackModifier *= 1.5;
  //       }
  //       if constexpr(otherResistantTo) {
  //           attackModifier *= 0.666;
  //       }
  //       return attackModifier;
  //   }
};

template <> struct ElementTypeTraits<FireType>
{
  typedef FireType Type;
  typedef TYPELIST1(GrassType) StrongAgainst;
  typedef TYPELIST2(WaterType, FireType) WeakAgainst;
  typedef TYPELIST2(GrassType, FireType) ResistantAgainst;
  typedef TYPELIST2(GroundType, WaterType) VulnerableAgainst;
};

template <> class ElementTypeTraits<WaterType>
{
  typedef WaterType Type;
  typedef TYPELIST2(GroundType, FireType) StrongAgainst;
  typedef TYPELIST2(WaterType, GrassType) WeakAgainst;
  typedef TYPELIST2(FireType, WaterType) ResistantAgainst;
  typedef TYPELIST2(GrassType, ElectricType) VulnerableAgainst;
};

template <> class ElementTypeTraits<GroundType>
{
  typedef GroundType Type;
  typedef TYPELIST2(ElectricType, FireType) StrongAgainst;
  typedef TYPELIST1(GrassType) WeakAgainst;
  typedef TYPELIST1(ElectricType) ResistantAgainst;
  typedef TYPELIST2(GrassType, WaterType) VulnerableAgainst;
};

template <> class ElementTypeTraits<GrassType>
{
  typedef GrassType Type;
  typedef TYPELIST2(GroundType, WaterType) StrongAgainst;
  typedef TYPELIST2(FireType, GrassType) WeakAgainst;
  typedef TYPELIST4(ElectricType, GrassType, WaterType,
                    GroundType) ResistantAgainst;
  typedef TYPELIST1(FireType) VulnerableAgainst;
};

template <> class ElementTypeTraits<ElectricType>
{
  typedef ElectricType Type;
  typedef TYPELIST1(WaterType) StrongAgainst;
  typedef TYPELIST3(GroundType, GrassType, ElectricType) WeakAgainst;
  typedef TYPELIST1(ElectricType) ResistantAgainst;
  typedef TYPELIST1(GroundType) VulnerableAgainst;
};

typedef boost::variant<
    ElementTypeTraits<ElectricType>, ElementTypeTraits<GrassType>,
    ElementTypeTraits<WaterType>, ElementTypeTraits<GroundType>,
    ElementTypeTraits<FireType>>
    ElementTypeTraitsVariants;

#endif
