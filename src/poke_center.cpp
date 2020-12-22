#include "include/poke_center.hpp"

void PokeCenter::Center::Heal(Pokemon& pokemon) 
{
    pokemon.setHealth_(pokemon.getMaxHealth_());
}

PokeBagItem* PokeCenter::Center::BuyPotion()
{
    return nullptr;
}

std::shared_ptr<PokeBagItem>&& PokeCenter::Center::BuyBall()
{
    std::cout << "What kind of Poke Balls would you like to buy?\n";
    std::string choice;
    std::cin >> choice;
    std::vector<std::shared_ptr<PokeBagItem>>::iterator it = find_if(balls_.begin(), balls_.end(),
                [choice](std::shared_ptr<PokeBagItem> &p) { return p->getType() == choice; });
    if(it == balls_.end()){
        std::cout << "error" << std::endl;
        return nullptr;
    }
    return std::move(*it);
}

