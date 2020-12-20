#ifndef ULTRABALL_HPP
#define ULTRABALL_HPP
#include "ball.hpp"
class UltraBall : public Ball {
public:
    UltraBall(){}
    void Catch() override
    {
        std::cout << " Using MasterBall" << std::endl;
    }

    void formatImpl(std::ostream &out) const override{
        out << "UltraBall";
    }

};
#endif