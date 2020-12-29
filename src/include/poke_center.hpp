#ifndef POKECENTER_HPP
#define POKECENTER_HPP

#include "exceptions/cancel_exception.hpp"
#include "game/player.hpp"
#include "poke_bag/ball/ball.hpp"
#include "poke_bag/ball/greatBall.hpp"
#include "poke_bag/ball/masterBall.hpp"
#include "poke_bag/ball/pokeBall.hpp"
#include "poke_bag/ball/ultraBall.hpp"
#include "poke_bag/pokeBag.hpp"
#include "poke_bag/pokeBagItem.hpp"
#include "poke_bag/potion/hyperPotion.hpp"
#include "poke_bag/potion/potion.hpp"
#include "poke_bag/potion/superPotion.hpp"
#include "pokemon/pokemon.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace PokeCenter
{

enum PokecenterChoice
{
  HealPokemon = 1,
  BuyItem     = 2
};

enum BuyItemChoice
{
  BuyPokeball = 1,
  BuyPotion   = 2
};

enum PokeCenterTypes
{
  PokeballType    = 0,
  GreatBallType   = 1,
  UltraballType   = 2,
  MasterballType  = 3,
  SuperpotionType = 4,
  HyperpotionType = 5
};

static std::vector<std::pair<std::string, double>> Items = {
    {"Pokeball", 200},    {"Greatball", 600},   {"Ultraball", 800},
    {"Masterball", 9001}, {"Superpotion", 700}, {"Hyperpotion", 1200}};

class Center
{

private:
  std::vector<std::shared_ptr<PokeBagItem>> pokeBagItems_;

  template <typename T>
  std::shared_ptr<PokeBagItem> createItem(PokeCenter::PokeCenterTypes type)
  {
    static_assert(std::is_base_of<PokeBagItem, T>::value,
                  "The type must be a base class of `PokeBagItem`");
    static_assert(
        std::is_convertible<T &, PokeBagItem &>::value,
        "The type must be an *accessible* base class of `PokeBagItem`");
    std::shared_ptr<T> t = std::make_shared<T>();
    t.get()->setPrice(PokeCenter::Items.at(type).second);
    t.get()->setType(PokeCenter::Items.at(type).first);
    return t; // shared_ptr will have count on 2, but then it will be
              // decremented to 1 immediatly after
  }

  void printItemsInShop()
  {
    auto i = 0;
    for (auto [first, second] : PokeCenter::Items)
    {
      std::cout << "#" << i << " " << first << ", Price:" << second << "\n";
      i++;
    }
    std::cout << std::endl;
  }
  template <typename T> void addToInventory(T &&item)
  {
    // Perfect forwarding of objekter for push_back
    pokeBagItems_.push_back(std::forward<T>(item)); // kalder den nødvendige push_back overload
  }

  std::shared_ptr<PokeBagItem> getPokeBagItem(const std::string choice,
                                         int &             indexToRemove);

public:
  Center()
  {
    for (size_t i = 0; i < 25; i++)
    {
      // we just want to MOVE the pointer of the shared_ptr, instead of
      // incrementing the counter and immediately after decrement it
      // Copies the ball into the inventory
      auto pokeBallItem =
          createItem<PokeBall>(PokeCenter::PokeCenterTypes::PokeballType);
      // forcer std::shared_ptr move-constructor
      addToInventory(pokeBallItem);
      //Moves ball into the inventory
      auto greatBallItem = createItem<GreatBall>(PokeCenter::PokeCenterTypes::GreatBallType);
      addToInventory(std::move(greatBallItem));
      addToInventory(createItem<UltraBall>(PokeCenter::PokeCenterTypes::UltraballType));
      addToInventory(createItem<MasterBall>(PokeCenter::PokeCenterTypes::MasterballType));
      addToInventory(createItem<SuperPotion>(PokeCenter::PokeCenterTypes::SuperpotionType));
      addToInventory(createItem<HyperPotion>(PokeCenter::PokeCenterTypes::HyperpotionType));
    }
    // for (size_t i = 0; i < pokeBagItems_.size(); i++)
    // {
    //     std::cout << pokeBagItems_.at(i).get()->getType() << "\n";
    // }
    // std::cout << std::endl;
  }

  void usePokecenter(Player &p);

  void                           heal(Pokemon &pokemon);
  std::shared_ptr<PokeBagItem> &&buyPotion();
  std::shared_ptr<PokeBagItem> &&buyBall();
  void                           listAvailableItems() { printItemsInShop(); }
  void                           buyPokeBagItem(PokeBag &playerBag);

  void addToBag(PokeBag &bag, std::shared_ptr<PokeBagItem> &&item);
};
} // namespace PokeCenter

#endif