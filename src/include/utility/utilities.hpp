#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>

namespace Utilities{

void clearScreen();// { std::cout << std::string(50, '\n'); }
void toLower(std::string& string);//{transform(string.begin(), string.end(), string.begin(), ::tolower);}

template<typename ForwardIt, typename UnaryPredicate>
inline ForwardIt select_random_if(ForwardIt first, ForwardIt last, UnaryPredicate predicate)
{
    std::vector<int> validElements;
    ForwardIt tempIt = first;
    int numElement = 0;
    for(; first != last; ++first, ++numElement)
    {
        if(predicate(*first))
        {
            validElements.emplace_back(numElement);
        }
    }
    if(validElements.size() == 0)
        return last;

    int randomElement = rand() % validElements.size();
    advance(tempIt, validElements[randomElement]);
    return tempIt;
}

}