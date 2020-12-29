#include <iostream>

namespace exceptions
{
    class UnknownPokemonTypeException : public std::exception
    {
    private:
        std::string ex_msg;

    public:
        UnknownPokemonTypeException(const std::string type)
            : ex_msg(std::string("The specified type: '") + type + std::string("' is not a known Pokemon type.")){};
        ~UnknownPokemonTypeException(){};

        virtual const char *what() const throw()
        {
            return ex_msg.c_str();
        }
    };
}