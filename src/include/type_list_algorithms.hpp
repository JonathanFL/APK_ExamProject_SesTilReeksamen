#ifndef TYPELISTALGORITHMS_HPP
#define TYPELISTALGORITHMS_HPP
#include "type_list.hpp"
#include "is_same.hpp"

template<typename TL, typename F>
struct Contains
{
    static const bool value = IsSame<typename TL::First, F>::value || Contains<typename TL::Rest, F>::value;
};


template<typename F>
struct Contains<NullType, F>
{
    static const bool value = false;
};

#endif