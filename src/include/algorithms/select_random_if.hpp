#include <cstdlib>
#include <vector>
template<typename ForwardIt, typename UnaryPredicate>
ForwardIt select_random_if(ForwardIt first, ForwardIt last, UnaryPredicate predicate)
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
    int randomElement = rand() % validElements.size();
    advance(tempIt, validElements[randomElement]);
    return tempIt;
}