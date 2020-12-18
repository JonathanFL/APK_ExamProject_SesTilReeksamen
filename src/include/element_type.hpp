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

template <typename T> 
struct IsDerivedElementType {
    static const bool value = std::is_base_of<ElementType, T>::value;
};

#endif
