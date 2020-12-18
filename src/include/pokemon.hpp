#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>
#include <iostream>
#include "poke_type.hpp"
#include "is_same.hpp"
#include "type_list_algorithms.hpp"

template<typename PrimaryType, typename SecondaryType>
class Pokemon
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
    /// ASD
    double getHealth_() { return this.health_; }
    void setHealth_(double health_) { this.health_ = health_; }
    int getLevel_() { return this.level_; }
    void setLevel_(int level_) { this.level_ = level_; }
    int getXp_() { return this.xp_; }
    void setXp_(int xp_) { this.xp_ = xp_; }
    double getAttack_() { return this.attack_; }
    void setAttack_(double attack_) { this.attack_ = attack_; }
    double getDefense_() { return this.defense_; }
    void setDefense_(double defense_) { this.defense_ = defense_; }
    std::string getName_() { return this.name_; }
    void setName_(std::string name_) { this.name_ = name_; }
    std::string getNickname_() { return this.nickname_; }
    void setNickname_(std::string nickname_) { this.nickname_ = nickname_; }

    PrimaryType   primaryType_;
    SecondaryType secondaryType_;
    Pokemon(double health, unsigned int level, unsigned int xp, double attack, double defense, std::string name, std::string nickname){
        static_assert(std::is_base_of<poketypes::PokemonType, PrimaryType>::value);
        static_assert(std::is_base_of<poketypes::PokemonType, SecondaryType>::value);
        static_assert(Contains<poketypes::PokemonTypeList,PrimaryType>::value);
        static_assert(Contains<poketypes::PokemonTypeList,PrimaryType>::value);
        this->health_ = health;
        this->level_ = level;
    }

    Pokemon();
    ~Pokemon();
};

#endif