#ifndef TYPELISTALGORITHMS_HPP
#define TYPELISTALGORITHMS_HPP
#include "is_same.hpp"
#include "type_list.hpp"
#include <type_traits>

template <typename TL, typename F> struct Contains
{
  static const bool value = IsSame<typename TL::First, F>::value ||
                            Contains<typename TL::Rest, F>::value;
};

template <typename F> struct Contains<NullType, F>
{
  static const bool value = false;
};

// template <typename TL, typename T> struct EveryIsBaseT
// {
//   static const bool value = std::is_base_of<T, typename TL::First>::value &&
//                             EveryIsBaseT<typename TL::Rest, T>::value;
// };

// template <typename T> struct EveryIsBaseT<NullType, T>
// {
//   static const bool value = true;
// };

template <typename TL, template<typename T> typename C> struct Every
{
  static const bool value =
   C<typename TL::First>::value && Every<typename TL::Rest, C>::value;
};

template <template<typename T> typename C> struct Every<NullType, C>
{
  static const bool value = true;
};
#endif