#ifndef MASTERBALL_HPP
#define MASTERBALL_HPP
#include "ball.hpp"
#include <chrono>
#include <thread>

class MasterBall : public Ball {
public:
    MasterBall(){}
    void Catch(std::function<void()> callback) override
    {
        std::cout << " Using MasterBall..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        callback();
    }

    void formatImpl(std::ostream &out) const override{
        out << "MasterBall";
    }

};
#endif