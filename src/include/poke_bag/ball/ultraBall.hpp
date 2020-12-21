#ifndef ULTRABALL_HPP
#define ULTRABALL_HPP
#include "ball.hpp"
#include <chrono>
#include <thread>


class UltraBall : public Ball {
private:
    const double probabilityOfCatch = .75;
    
public:
    UltraBall(){}
    void Catch(std::function<void(PokeBagItemResult res)> callback) override
    {
        std::cout << "Using UltraBall: probability of catching is " << 0.75_to_percent << "%" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PokeBagItemResult res;res.result = caught(probabilityOfCatch) ? caughtSuccessMessage : caughtFailMessage;
        callback(res);
    }

    void formatImpl(std::ostream &out) const override{
        out << "UltraBall";
    }

};
#endif