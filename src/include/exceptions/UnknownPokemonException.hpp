#pragma once
#include <exception>
#include <string>
namespace exceptions
{
    struct UnknownPokemonException : public std::exception
    {
        const char *what() const throw()
        {
            return "Unknown pokemon... Please enter the name of a pokemon from your bag!";
        }
    };
} // namespace exceptions
