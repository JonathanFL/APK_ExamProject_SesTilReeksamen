#ifndef SUPERPOTION_HPP
#define SUPERPOTION_HPP
#include "potion.hpp"
#include <chrono>
#include <thread>

class SuperPotion : public Potion {
public:
    SuperPotion(){}
    void UsePotion(std::function<void()> callback) override
    {
        std::cout << " Using SuperPotion..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        callback();
    }

    void formatImpl(std::ostream &out) const override{
        out << "SuperPotion";
    }

};
#endif