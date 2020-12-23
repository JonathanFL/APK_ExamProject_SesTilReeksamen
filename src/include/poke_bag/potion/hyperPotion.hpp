#ifndef HYPERPOTION_HPP
#define HYPERPOTION_HPP
#include "potion.hpp"
#include <chrono>
#include <thread>

class HyperPotion : public Potion {
private:
    const unsigned int healAmount = 200;
public:
    HyperPotion(){}
    void UsePotion(Pokemon& pokemon,std::function<void(PokeBagItemResult res)> callback) override
    {
        std::cout << " Using HyperPotion..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        PokeBagItemResult res;res.result = heal(pokemon, healAmount) ? pokemon.getNickname_() + " was healed HP" : "Potion failed";
        callback(res);
    }

    void formatImpl(std::ostream &out) const override{
        out << "SuperPotion healing: " << std::to_string(healAmount);
    }

};
#endif