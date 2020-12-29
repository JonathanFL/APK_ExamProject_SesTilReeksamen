#pragma once
#include <exception>
#include <string>
namespace exceptions
{
struct NoPotionsException : public std::exception
{
    const char *what() const throw()
    {
        return "No available potions...";
    }
};
}
