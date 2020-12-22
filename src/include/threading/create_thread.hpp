#include "future"
#include <thread>
template<typename R, typename Function>
std::future<R> createFuture(Function & function) 
{
    std::promise<R> p;
    std::future<R> f = p.get_future();
    std::thread(function, std::move(p)).detach();
    return f;
}