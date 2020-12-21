#ifndef BALL_HPP
#define BALL_HPP
#include "../pokeBagItem.hpp"
#include <iostream>
#include <random>

class Ball : public PokeBagItem {
public:
    Ball(){}
    
    bool caught(int probabilityOfCatch){
        std::random_device rd;
        std::uniform_int_distribution<int> distribution(1, 100);
        std::mt19937 engine(rd()); // Mersenne twister MT19937

        int value=distribution(engine);
        return value < probabilityOfCatch;
    };

    void Use(std::function<void(PokeBagItemResult res)> callback) override{
        Catch(callback);
    }
    void format(std::ostream &out) const override{
        this->formatImpl(out);
    }

    virtual void formatImpl(std::ostream &out) const = 0;

    virtual void Catch(std::function<void(PokeBagItemResult res)> callback) = 0;

    virtual~Ball();
private:
    
};

#endif
