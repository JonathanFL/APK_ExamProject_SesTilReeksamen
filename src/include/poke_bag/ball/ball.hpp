#ifndef BALL_HPP
#define BALL_HPP
#include "../pokeBagItem.hpp"
#include <iostream>

class Ball : public PokeBagItem {
public:
    Ball(){}

    void Use() override{

    }
    void format(std::ostream &out) const override{
        this->formatImpl(out);
    }
    // {
    //     out << "======== DERIVED1 ========" << std::endl;
    //     out << "derived1" << std::endl;
    //     out << "======== DERIVED1 ========" << std::endl;
    //     formatImpl(out);
    // }

    virtual void formatImpl(std::ostream &out) const = 0;

    virtual void Catch() = 0;

    virtual~Ball();
private:
    
};

#endif
