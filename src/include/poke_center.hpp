#ifndef POKECENTER_HPP
#define POKECENTER_HPP

#include "poke_bag/pokeBagItem.hpp"
#include "poke_bag/potion/potion.hpp"
#include <vector>

class PokeCenter{
private:
    //std::vector<
public:
    PokeBagItem BuyPotion();
    PokeBagItem BuyBall();
};

#endif