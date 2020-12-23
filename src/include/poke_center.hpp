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
#include "game/player.hpp"

#include <vector>
#include <memory>


namespace PokeCenter{

enum PokecenterChoice {
    HealPokemon = 1,
    BuyItem = 2
};

enum BuyItemChoice {
    BuyPokeball = 1,
    BuyPotion = 2
};

static std::vector<std::pair<std::string, double>> Items = {
    {"Pokeball",200},{"Greatball",600},{"Ultraball",800},{"Masterball",9001},{"Superpotion",700},{"Hyperpotion",1200}
};
class Center{

private:
    std::vector<std::shared_ptr<PokeBagItem>> balls_;
    std::vector<std::shared_ptr<PokeBagItem>> potions_;

    template<typename T>
    std::shared_ptr<PokeBagItem>&& createItem(double price, std::string type){
        static_assert(std::is_base_of<PokeBagItem, T>::value, "The type must be a base class of `PokeBagItem`");
        static_assert(std::is_convertible<T&, PokeBagItem&>::value, "The type must be an *accessible* base class of `PokeBagItem`");
        std::shared_ptr<T> t = std::make_shared<T>();
        T* pbitem = t.get();
        pbitem->setPrice(price);
        pbitem->setType(type);
        return std::move(t);
    }

    void printItemsInShop()
    {
        std::cout << "Available items:" << "\n"; 
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
            balls_.push_back(createItem<PokeBall>(PokeCenter::Items.at(0).second,PokeCenter::Items.at(0).first));
            balls_.push_back(createItem<GreatBall>(PokeCenter::Items.at(1).second,PokeCenter::Items.at(1).first));
            balls_.push_back(createItem<UltraBall>(PokeCenter::Items.at(2).second,PokeCenter::Items.at(2).first));
            balls_.push_back(createItem<MasterBall>(PokeCenter::Items.at(3).second,PokeCenter::Items.at(3).first));

            potions_.push_back(createItem<SuperPotion>(PokeCenter::Items.at(4).second,PokeCenter::Items.at(4).first));
            potions_.push_back(createItem<HyperPotion>(PokeCenter::Items.at(5).second,PokeCenter::Items.at(5).first));
        }
    }

    void usePokecenter(Player &p);

    void Heal(Pokemon& pokemon);
    std::shared_ptr<PokeBagItem>&& BuyPotion();
    std::shared_ptr<PokeBagItem>&& BuyBall();
    void ListAvailableItems(){
        printItemsInShop();
    }
    std::shared_ptr<PokeBagItem> buyPokeBagItem();
};
}

#endif