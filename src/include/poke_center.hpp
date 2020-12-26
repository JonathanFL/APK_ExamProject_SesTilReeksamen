#ifndef POKECENTER_HPP
#define POKECENTER_HPP

#include "pokemon/pokemon.hpp"
#include "poke_bag/pokeBagItem.hpp"
#include "poke_bag/pokeBag.hpp"
#include "poke_bag/potion/potion.hpp"
#include "poke_bag/ball/ball.hpp"
#include "poke_bag/ball/masterBall.hpp"
#include "poke_bag/ball/pokeBall.hpp"
#include "poke_bag/ball/greatBall.hpp"
#include "poke_bag/ball/ultraBall.hpp"
#include "poke_bag/potion/hyperPotion.hpp"
#include "poke_bag/potion/superPotion.hpp"
#include "game/player.hpp"
#include "exceptions/cancel_exception.hpp"

#include <vector>
#include <memory>
#include <functional>


namespace PokeCenter{

enum PokecenterChoice {
    HealPokemon = 1,
    BuyItem = 2
};

enum BuyItemChoice {
    BuyPokeball = 1,
    BuyPotion = 2
};

enum PokeCenterTypes {
    PokeballType = 0,
    GreatBallType = 1,
    UltraballType = 2,
    MasterballType = 3,
    SuperpotionType = 4,
    HyperpotionType = 5
};

static std::vector<std::pair<std::string, double>> Items = {
    {"Pokeball",200},{"Greatball",600},{"Ultraball",800},{"Masterball",9001},{"Superpotion",700},{"Hyperpotion",1200}
};

class Center{

private:
    std::vector<std::shared_ptr<PokeBagItem>> balls_;
    std::vector<std::shared_ptr<PokeBagItem>> potions_;

    template<typename T>
    std::shared_ptr<PokeBagItem> createItem(PokeCenter::PokeCenterTypes type){
        static_assert(std::is_base_of<PokeBagItem, T>::value, "The type must be a base class of `PokeBagItem`");
        static_assert(std::is_convertible<T&, PokeBagItem&>::value, "The type must be an *accessible* base class of `PokeBagItem`");
        std::shared_ptr<T> t = std::make_shared<T>();
        t.get()->setPrice(PokeCenter::Items.at(type).second);
        t.get()->setType(PokeCenter::Items.at(type).first);
        return t;// return by rvalue ref(xvalue?), temporary variable, t, is extended beyond the rvalue ref definition
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

    void addBallToInventory(std::shared_ptr<PokeBagItem>&& item)
    {
        balls_.push_back(std::forward<std::shared_ptr<PokeBagItem>>(item));
    }

    void addPotionToInventory(std::shared_ptr<PokeBagItem>&& item)
    {
        potions_.push_back(std::forward<std::shared_ptr<PokeBagItem>>(item));
    }

public:

    Center()
    {
        for (size_t i = 0; i < 20; i++)
        {
            addBallToInventory(std::move(createItem<PokeBall>(PokeCenter::PokeCenterTypes::PokeballType)));
            addBallToInventory(std::move(createItem<GreatBall>(PokeCenter::PokeCenterTypes::GreatBallType)));
            addBallToInventory(std::move(createItem<UltraBall>(PokeCenter::PokeCenterTypes::UltraballType)));
            addBallToInventory(std::move(createItem<MasterBall>(PokeCenter::PokeCenterTypes::MasterballType)));

            addPotionToInventory(std::move(createItem<SuperPotion>(PokeCenter::PokeCenterTypes::SuperpotionType)));
            addPotionToInventory(std::move(createItem<HyperPotion>(PokeCenter::PokeCenterTypes::HyperpotionType)));
        }
    }

    void usePokecenter(Player &p);

    void heal(Pokemon& pokemon);
    std::shared_ptr<PokeBagItem>&& buyPotion();
    std::shared_ptr<PokeBagItem>&& buyBall();
    void listAvailableItems(){
        printItemsInShop();
    }
    std::shared_ptr<PokeBagItem>&&  buyPokeBagItem();
};
}

#endif