#include "include/poke_center.hpp"

void PokeCenter::Center::Heal(Pokemon& pokemon) 
{
    pokemon.setHealth_(pokemon.getMaxHealth_());
}

std::shared_ptr<PokeBagItem>&& PokeCenter::Center::BuyPotion()
{
    std::cout << "Enter the name of the Potion you would like to buy\n";
    std::string choice;
    std::cin >> choice;
    std::vector<std::shared_ptr<PokeBagItem>>::iterator it = find_if(potions_.begin(), potions_.end(),
                [choice](std::shared_ptr<PokeBagItem> &p) { return p->getType() == choice; });
    if(it == potions_.end()){
        return nullptr;
    }
    return std::move(*it);
}

std::shared_ptr<PokeBagItem>&& PokeCenter::Center::BuyBall()
{
    std::cout << "Enter the name of the Poke ball you would like to buy\n";
    std::string choice;
    std::cin >> choice;
    std::vector<std::shared_ptr<PokeBagItem>>::iterator it = find_if(balls_.begin(), balls_.end(),
                [choice](std::shared_ptr<PokeBagItem> &p) { return p->getType() == choice; });
    if(it == balls_.end()){
        return nullptr;
    }
    return std::move(*it);
}

