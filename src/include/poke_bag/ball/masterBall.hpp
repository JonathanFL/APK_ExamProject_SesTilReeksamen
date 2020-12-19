#ifndef MASTERBALL_HPP
#define MASTERBALL_HPP
#include "ball.hpp"
class MasterBall : Ball {
public:
    virtual void Catch(){
        std::cout << " Using MasterBall" << std::endl;
    }
};
#endif