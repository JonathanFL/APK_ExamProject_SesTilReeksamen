#ifndef MASTERBALL_HPP
#define MASTERBALL_HPP
#include "ball.hpp"
class MasterBall : public Ball {
public:
    MasterBall(){}
    void Catch() override
    {
        std::cout << " Using MasterBall" << std::endl;
    }

    void formatImpl(std::ostream &out) const override{
        out << "MasterBall";
    }

};
#endif