#ifndef SUPERPOTION_HPP
#define SUPERPOTION_HPP
#include "potion.hpp"
#include <chrono>
#include <thread>

class SuperPotion : public Potion {
public:
    SuperPotion(){}
    void UsePotion(std::function<void(PokeBagItemResult res)> callback) override
    {
        std::cout << " Using SuperPotion..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PokeBagItemResult res;res.result = std::to_string(100);
        callback(res);
    }

    void formatImpl(std::ostream &out) const override{
        out << "SuperPotion";
    }

};
#endif