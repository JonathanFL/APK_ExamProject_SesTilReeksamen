#ifndef MASTERBALL_HPP
#define MASTERBALL_HPP
#include "ball.hpp"
#include <chrono>
#include <thread>

class MasterBall : public Ball {
private:
    const double probabilityOfCatch = 1;
public:
    MasterBall(){}
    void Catch(Pokemon& pokemon, std::function<void(PokeBagItemResult res)> callback) override
    {
        std::cout << "Using UltraBall: probability of catching is " << 1.0_to_percent << "%" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PokeBagItemResult res;
        res.result = caught(probabilityOfCatch) ? caughtSuccessMessage : caughtFailMessage;
        callback(res);
    }

    void formatImpl(std::ostream &out) const override{
        out << "Masterball";
    }

};
#endif