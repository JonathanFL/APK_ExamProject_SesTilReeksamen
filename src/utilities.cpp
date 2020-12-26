#include "include/utility/utilities.hpp"

namespace Utilities{
    
    void clearScreen()
    {
        std::cout << std::string(50, '\n');
    }

    void toLower(std::string& string){
        transform(string.begin(), string.end(), string.begin(), ::tolower);
    }

}