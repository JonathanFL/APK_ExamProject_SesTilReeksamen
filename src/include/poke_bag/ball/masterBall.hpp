#ifndef MASTERBALL_HPP
#define MASTERBALL_HPP
#include "ball.hpp"
#include <chrono>
#include <thread>

class MasterBall : public Ball {
private:
    const unsigned int probabilityOfCatch = 100;
public:
    MasterBall(){}
    void Catch(std::function<void(PokeBagItemResult res)> callback) override
    {
        std::cout << " Using MasterBall..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PokeBagItemResult res;res.result = caught(probabilityOfCatch) ? "You caught the Pokemon" : "You did NOT catch the Pokemon";
        callback(res);
    }

    void formatImpl(std::ostream &out) const override{
        out << "MasterBall";
    }

};
#endif