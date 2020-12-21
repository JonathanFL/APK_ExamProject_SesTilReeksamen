#ifndef HYPERPOTION_HPP
#define HYPERPOTION_HPP
#include "potion.hpp"
#include <chrono>
#include <thread>

class HyperPotion : public Potion {
public:
    HyperPotion(){}
    void UsePotion(std::function<void()> callback) override
    {
        std::cout << " Using HyperPotion..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        callback();
    }

    void formatImpl(std::ostream &out) const override{
        out << "HyperPotion";
    }

};
#endif