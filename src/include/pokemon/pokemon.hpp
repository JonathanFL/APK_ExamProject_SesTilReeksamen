#ifndef POKEMON_HPP
#define POKEMON_HPP

#include "../metaprogramming/is_same.hpp"
#include "../metaprogramming/type_list_algorithms.hpp"
#include "poke_type.hpp"
#include "poke_type_factory.hpp"
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class Pokemon
{
private:
  /* data */
  double health_;
  unsigned int level_;
  unsigned int xp_;
  double attack_;
  double defense_;
  std::string name_;
  std::string nickname_;
  poketypes::PokemonTypeVariant pType_;
  poketypes::PokemonTypeVariant sType_;

public:
  const double getHealth_() const { return this->health_; }
  void setHealth_(double health_) { this->health_ = health_; }
  const int getLevel_() const { return this->level_; }
  void setLevel_(int level_) { this->level_ = level_; }
  const int getXp_() const { return this->xp_; }
  void setXp_(int xp_) { this->xp_ = xp_; }
  const double getAttack_() const { return this->attack_; }
  void setAttack_(double attack_) { this->attack_ = attack_; }
  const double getDefense_() const { return this->defense_; }
  void setDefense_(double defense_) { this->defense_ = defense_; }
  const std::string getName_() const { return this->name_; }
  void setName_(std::string name_) { this->name_ = name_; }
  const std::string getNickname_() const { return this->nickname_; }
  void setNickname_(std::string nickname_) { this->nickname_ = nickname_; }
  poketypes::PokemonTypeVariant getPrimaryType() const { return pType_; }
  poketypes::PokemonTypeVariant getSecondaryType() const { return sType_; }

  Pokemon(double health, unsigned int level, unsigned int xp, double attack,
          double defense, std::string &&name, std::string &&nickname,
          poketypes::PokemonTypeVariant &&primaryType,
          poketypes::PokemonTypeVariant &&secondaryType)
  {
    this->health_ = health;
    this->level_ = level;
    this->name_ = std::move(name);
    this->nickname_ = std::move(nickname);
    this->xp_ = xp;
    this->attack_ = attack;
    this->defense_ = defense;
    sType_ = std::move(secondaryType);
    pType_ = std::move(primaryType);
  }

  Pokemon(double health, unsigned int level, unsigned int xp, double attack,
          double defense, std::string &&name, std::string &&nickname,
          poketypes::PokemonTypeVariant &&primaryType)
  {
    this->health_ = health;
    this->level_ = level;
    this->name_ = std::move(name);
    this->nickname_ = std::move(nickname);
    this->xp_ = xp;
    this->attack_ = attack;
    this->defense_ = defense;
    pType_ = std::move(primaryType);
    sType_ = poketypes::PokemonTypeVariant();
  }

  std::string battleCry() { return name_ + name_ + "!!"; }

  double getModifier(Pokemon &other)
  {
    double modifier = 1;
    poketypes::PokemonTypeVariant pt = other.getPrimaryType();
    poketypes::PokemonTypeVariant st = other.getSecondaryType();
    modifier *= boost::apply_visitor(poketypes::PokemonTypeModifierVisitor(),
                                     pType_, pt);
    modifier *= boost::apply_visitor(poketypes::PokemonTypeModifierVisitor(),
                                     pType_, st);
    modifier *= boost::apply_visitor(poketypes::PokemonTypeModifierVisitor(),
                                     sType_, pt);
    modifier *= boost::apply_visitor(poketypes::PokemonTypeModifierVisitor(),
                                     sType_, st);
    modifier *= attack_ / other.getDefense_();
    return modifier;
  }

  Pokemon()
      : health_(0),
        level_(0),
        xp_(0),
        attack_(0),
        defense_(0),
        name_(""),
        nickname_("")
  {
  }
  ~Pokemon() {}

  friend std::istream &operator>>(std::istream &in, Pokemon &p)
  {
    std::string nickname, primaryType, secondaryType;

    in >> nickname;
    if (nickname.empty())
    {
      return in;
    }
    nickname != "null" ? p.nickname_ = nickname : p.nickname_ = "";

    in >> p.name_;

    in >> primaryType;
    p.pType_ = poketypes::PokeTypeFactory().getPokeTypeFromString(primaryType);

    in >> secondaryType;
    if (secondaryType != "null")
    {
      p.sType_ = poketypes::PokeTypeFactory().getPokeTypeFromString(secondaryType);
    }

    in >> p.health_;
    in >> p.level_;
    in >> p.xp_;
    in >> p.attack_;
    return in >> p.defense_;
  };

  friend std::ostream &operator<<(std::ostream &out, const Pokemon &p)
  {
    return out << "Pokemon: " << p.getName_()
               << " - Attack: " << to_string(p.getAttack_())
               << " - Health: " << to_string(p.getHealth_())
               << " - Level: " << to_string(p.getLevel_())
               << " - XP: " << to_string(p.getXp_())
               << " - Nickname: " << p.getNickname_()
               << std::endl;
  }
};

typedef std::vector<Pokemon> PokemonList;

#endif