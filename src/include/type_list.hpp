struct NullType{};

template<typename L, typename R>
struct TypeList 
{
    typedef L First;
    typedef R Rest;
};
