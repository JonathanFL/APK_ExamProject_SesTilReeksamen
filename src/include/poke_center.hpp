#ifndef POKECENTER_HPP
#define POKECENTER_HPP

#include "pokemon/pokemon.hpp"
#include "poke_bag/pokeBagItem.hpp"
#include "poke_bag/potion/potion.hpp"
#include "poke_bag/ball/ball.hpp"
#include "poke_bag/ball/masterBall.hpp"
#include "poke_bag/ball/pokeBall.hpp"
#include "poke_bag/ball/greatBall.hpp"
#include "poke_bag/ball/ultraBall.hpp"
#include "poke_bag/potion/hyperPotion.hpp"
#include "poke_bag/potion/superPotion.hpp"

#include <vector>
#include <memory>

namespace PokeCenter{
static std::vector<std::pair<std::string, double>> Items = {
    {"Pokeball",200},{"Greatball",600},{"Ultraball",800},{"Masterball",9001},{"Superpotion",700},{"Hyperpotion",1200}
};
class Center{

private:
    std::vector<std::shared_ptr<PokeBagItem>> balls_;
    std::vector<std::shared_ptr<PokeBagItem>> potions_;
    
    std::shared_ptr<PokeBagItem> createPokeBall()
    {
        std::shared_ptr<PokeBall> pokeBall = std::make_shared<PokeBall>();
        PokeBall* pbitem = pokeBall.get();
        pbitem->setPrice(PokeCenter::Items.at(0).second);
        pbitem->setType(PokeCenter::Items.at(0).first);
        return pokeBall;
    }
    std::shared_ptr<PokeBagItem> createGreatBall()
    {
        std::shared_ptr<GreatBall> greatBall = std::make_shared<GreatBall>();
        GreatBall* pbitem = greatBall.get();
        pbitem->setPrice(PokeCenter::Items.at(1).second);
        pbitem->setType(PokeCenter::Items.at(1).first);
        return greatBall;
    }
    std::shared_ptr<PokeBagItem> createUltraBall()
    {
        std::shared_ptr<UltraBall> ultraBall = std::make_shared<UltraBall>();
        UltraBall* pbitem = ultraBall.get();
        pbitem->setPrice(PokeCenter::Items.at(2).second);
        pbitem->setType(PokeCenter::Items.at(2).first);
        return ultraBall;
    }
    std::shared_ptr<PokeBagItem> createMasterBall()
    {
        std::shared_ptr<MasterBall> masterBall = std::make_shared<MasterBall>();
        MasterBall* pbitem = masterBall.get();
        pbitem->setPrice(PokeCenter::Items.at(3).second);
        pbitem->setType(PokeCenter::Items.at(3).first);
        return masterBall;
    }

    void printItemsInShop()
    {
        auto i = 0;
        for(auto [first,second] : PokeCenter::Items){
            std::cout << "#" << i << " " << first << ", Price:" << second << "\n";
            i++;
        }
        std::cout << std::endl;
    }

public:

    Center()
    {
        for (size_t i = 0; i < 20; i++)
        {
            balls_.push_back(createPokeBall());
            balls_.push_back(createGreatBall());
            balls_.push_back(createUltraBall());
            balls_.push_back(createMasterBall());
        }
    }

    void Heal(Pokemon& pokemon);
    PokeBagItem* BuyPotion();
    std::shared_ptr<PokeBagItem>&& BuyBall();
    void ListAvailableItems(){
        printItemsInShop();
    }
};
}

#endif