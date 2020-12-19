#ifndef BALL_HPP
#define BALL_HPP
#include "../pokeBagItem.hpp"
#include <iostream>

class Ball : PokeBagItem {
public:
    void Use (){
		std::cout << " Using ball";
        Catch();
    }
    virtual void Catch() = 0;
};
#endif
