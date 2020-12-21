#ifndef ULTRABALL_HPP
#define ULTRABALL_HPP
#include "ball.hpp"
#include <chrono>
#include <thread>
#include <string>

class UltraBall : public Ball {
private:
    const unsigned int probabilityOfCatch = 75;
    
public:
    UltraBall(){}
    void Catch(std::function<void(PokeBagItemResult res)> callback) override
    {
        std::cout << " Using UltraBall: probability of catching is " << std::to_string(probabilityOfCatch) << "%" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PokeBagItemResult res;res.result = caught(probabilityOfCatch) ? "You caught the Pokemon" : "You did NOT catch the Pokemon";
        callback(res);
    }

    void formatImpl(std::ostream &out) const override{
        out << "UltraBall";
    }

};
#endif