#include <iostream>

namespace dbloader
{
    class FileNotFoundException : public std::exception
    {
    private:
        std::string ex_msg;

    public:
        FileNotFoundException(const std::string file)
            : ex_msg(std::string("Unable to open the specified file: '") + file + std::string("'.")){};
        ~FileNotFoundException(){};

        virtual const char *what() const throw()
        {
            return ex_msg.c_str();
        }
    };
}