#ifndef HYPERPOTION_HPP
#define HYPERPOTION_HPP
#include "potion.hpp"
#include <chrono>
#include <thread>

class HyperPotion : public Potion {
public:
    HyperPotion(){}
    void UsePotion(std::function<void(PokeBagItemResult res)> callback) override
    {
        std::cout << " Using HyperPotion..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PokeBagItemResult res;res.result = std::to_string(100);
        callback(res);
    }

    void formatImpl(std::ostream &out) const override{
        out << "HyperPotion";
    }

};
#endif