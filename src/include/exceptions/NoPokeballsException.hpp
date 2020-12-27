#pragma once
#include <exception>
#include <string>

struct NoPokeballsException : public std::exception
{
    const char *what() const throw()
    {
        return "No available pokeballs...";
    }
};
