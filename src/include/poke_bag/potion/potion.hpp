#ifndef POTION_HPP
#define POTION_HPP

#include "../pokeBagItem.hpp"
#include <iostream>

class Potion : public PokeBagItem {
public:
    Potion(){}

    void Use(std::function<void()> callback) override{
        UsePotion(callback);
    }
    void format(std::ostream &out) const override{
        this->formatImpl(out);
    }

    virtual void formatImpl(std::ostream &out) const = 0;

    virtual void UsePotion(std::function<void()> callback) = 0;

    virtual~Potion();
private:
    
};

#endif