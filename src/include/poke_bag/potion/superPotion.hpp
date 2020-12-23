#ifndef SUPERPOTION_HPP
#define SUPERPOTION_HPP
#include "potion.hpp"
#include <chrono>
#include <thread>

class SuperPotion : public Potion {
private:
    const unsigned int healAmount = 50;
public:
    SuperPotion(){}
    void UsePotion(Pokemon& pokemon, std::function<void(PokeBagItemResult res)> callback) override
    {
        std::cout << " Using SuperPotion..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PokeBagItemResult res;res.result = heal(pokemon, healAmount) ? pokemon.getNickname_() + " was healed" : "Potion failed";
        callback(res);
    }

    void formatImpl(std::ostream &out) const override{
        out << "SuperPotion healing: " << std::to_string(healAmount);
    }

};
#endif