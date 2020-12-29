#ifndef TYPELISTALGORITHMS_HPP
#define TYPELISTALGORITHMS_HPP
#include "is_same.hpp"
#include "type_list.hpp"
#include <type_traits>

template <typename TL, typename F>
struct Contains
{
  static constexpr bool value = IsSame<typename TL::First, F>::value ||
                                Contains<typename TL::Rest, F>::value;
};

template <typename F>
struct Contains<NullType, F>
{
  static constexpr bool value = false;
};

template <typename TL, template <typename T> typename C>
struct Every
{
  static constexpr bool value =
      C<typename TL::First>::value && Every<typename TL::Rest, C>::value;
};

template <template <typename T> typename C>
struct Every<NullType, C>
{
  static constexpr bool value = true;
};
#endif