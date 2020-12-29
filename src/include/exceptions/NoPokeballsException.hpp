#pragma once
#include <exception>
#include <string>
namespace exceptions
{
struct NoPokeballsException : public std::exception
{
    const char *what() const throw()
    {
        return "No available pokeballs...";
    }
};
}
