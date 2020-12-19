#ifndef ISSAME_HPP
#define ISSAME_HPP
template<typename T0, typename T1>
struct IsSame  {
    static constexpr bool value = false;
};

template<typename T>
struct IsSame<T, T>  {
    static constexpr bool value = true;
};

#endif