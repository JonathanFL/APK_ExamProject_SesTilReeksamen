#ifndef TYPELIST_HPP
#define TYPELIST_HPP
#define TYPELIST1(arg1) TypeList<arg1, NullType>
#define TYPELIST2(arg1, arg2) TypeList<arg1, TYPELIST1(arg2)>
#define TYPELIST3(arg1, arg2, arg3) TypeList<arg1, TYPELIST2(arg2, arg3)>
#define TYPELIST4(arg1, arg2, arg3, arg4) TypeList<arg1, TYPELIST3(arg2, arg3,arg4)>
#define TYPELIST5(arg1, arg2, arg3, arg4, arg5) TypeList<arg1, TYPELIST4(arg2, arg3,arg4, arg5)>
#define TYPELIST6(arg1, arg2, arg3, arg4, arg5, arg6) TypeList<arg1, TYPELIST5(arg2, arg3,arg4, arg5, arg6)>
#define TYPELIST7(arg1, arg2, arg3, arg4, arg5, arg6, arg7) TypeList<arg1, TYPELIST6(arg2, arg3,arg4, arg5, arg6, arg7)>

struct NullType{};
template <typename L, typename R>
struct TypeList
{
    typedef L First;
    typedef R Rest;
};

#endif