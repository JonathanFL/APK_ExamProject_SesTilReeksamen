#ifndef ULTRABALL_HPP
#define ULTRABALL_HPP
#include "ball.hpp"
#include <chrono>
#include <thread>
#include <random>

class UltraBall : public Ball {
private:
    unsigned int probabilityOfCatch = 75;
    bool caught_ = [](){
        std::random_device rd;
        std::uniform_int_distribution<int> distribution(1, 100);
        std::mt19937 engine(rd()); // Mersenne twister MT19937

        int value=distribution(engine);
        return value > 75;
    };
public:
    UltraBall(){}
    void Catch(std::function<void()> callback) override
    {
        std::cout << " Using UltraBall..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        callback();
    }

    void formatImpl(std::ostream &out) const override{
        out << "UltraBall";
    }

};
#endif