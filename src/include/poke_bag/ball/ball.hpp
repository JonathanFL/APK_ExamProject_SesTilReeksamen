#ifndef BALL_HPP
#define BALL_HPP
#include "../pokeBagItem.hpp"
#include <iostream>

class Ball : public PokeBagItem {
public:
    Ball(){}

    void Use(std::function<void()> callback) override{
        Catch(callback);
    }
    void format(std::ostream &out) const override{
        this->formatImpl(out);
    }

    virtual void formatImpl(std::ostream &out) const = 0;

    virtual void Catch(std::function<void()> callback) = 0;

    virtual~Ball();
private:
    
};

#endif
