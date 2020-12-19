#ifndef POKEMON_HPP
#define POKEMON_HPP

#include "is_same.hpp"
#include "poke_type.hpp"
#include "type_list_algorithms.hpp"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;
class IPokemon {

};

class UndiscoveredPokemon : public IPokemon 
{
    
};

template <typename PrimaryType, typename SecondaryType> class Pokemon : public IPokemon
{
private:
  /* data */
  double       health_;
  unsigned int level_;
  unsigned int xp_;
  double       attack_;
  double       defense_;
  std::string  name_;
  std::string  nickname_;

public:
  const double      getHealth_() const { return this->health_; }
  void        setHealth_(double health_) { this->health_ = health_; }
  const int         getLevel_() const { return this->level_; }
  void        setLevel_(int level_) { this->level_ = level_; }
  const int         getXp_() const { return this->xp_; }
  void        setXp_(int xp_) { this->xp_ = xp_; }
  const double      getAttack_() const{ return this->attack_; }
  void        setAttack_(double attack_) { this->attack_ = attack_; }
  const double      getDefense_() const { return this->defense_; }
  void        setDefense_(double defense_) { this->defense_ = defense_; }
  const std::string getName_() const { return this->name_; }
  void        setName_(std::string name_) { this->name_ = name_; }
  const std::string getNickname_() const { return this->nickname_; }
  void setNickname_(std::string nickname_) { this->nickname_ = nickname_; }

  Pokemon(double health, unsigned int level, unsigned int xp, double attack,
          double defense, std::string name, std::string nickname)
  {
    // static_assert(std::is_base_of<poketypes::PokemonType<>,
    // PrimaryType>::value);
    // static_assert(std::is_base_of<poketypes::PokemonType,
    // SecondaryType>::value);
    static_assert(Contains<poketypes::PokemonTypeList, PrimaryType>::value, "Must be a PokemonType");
    static_assert(Contains<poketypes::PokemonTypeList, SecondaryType>::value, "Must be a PokemonType");
    this->health_ = health;
    this->level_  = level;
    this->name_ = name;
    this->nickname_ = nickname;
    this->xp_ = xp;
    this->attack_ = attack;
    this->defense_ = defense;
  }

  Pokemon() : health_(0), level_(0),xp_(0),attack_(0),defense_(0),name_(""), nickname_("") {}
  ~Pokemon() {}

  
};

// toString
template<typename PrimaryType,typename SecondaryType>
std::ostream &operator<<(std::ostream& out, const Pokemon<PrimaryType, SecondaryType> &v)
{
    return out << "Pokemon: "
    << v.getName_()
    << " - Attack: "
    << to_string(v.getAttack_())
    << " - Health: "
    << to_string(v.getHealth_())
    << " - Level: "
    << to_string(v.getLevel_())
    << " - XP: "
    << to_string(v.getXp_())
    << " - Nickname: " << v.getNickname_();
}

#endif