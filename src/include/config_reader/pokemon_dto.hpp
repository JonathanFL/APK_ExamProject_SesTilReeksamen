#include <iostream>
#include "../pokemon/poke_type.hpp"

class PokemonDto
{
private:
    std::string name_;
    std::string nickname_;
    std::string primaryType_;
    std::string secondaryType_;
    double health_;
    int level_;
    int xp_;
    double attack_;
    double defense_;

public:
    PokemonDto(const std::string &name, const std::string &nickname, const std::string &primaryType, const std::string &secondaryType, double health, int level, int xp, double attack, double defense)
        : name_(name), nickname_(nickname), primaryType_(primaryType), secondaryType_(secondaryType), health_(health), level_(level), xp_(xp), attack_(attack), defense_(defense)
    {
    }
    PokemonDto() : name_(""), nickname_(""), primaryType_(""), secondaryType_(""), health_(0.0), level_(0), xp_(0), attack_(0.0), defense_(0.0) {}

    const std::string &name() const
    {
        return name_;
    }

    const std::string &nickname() const
    {
        return nickname_;
    }

    const poketypes::PokemonTypeVariant primaryType() const
    {
        return poketypes::PokemonTypeFactory().getPokemonType(primaryType_);
    }

    const poketypes::PokemonTypeVariant secondaryType() const
    {
        return poketypes::PokemonTypeFactory().getPokemonType(secondaryType_);
    }

    double &health()
    {
        return health_;
    }

    const int &level() const
    {
        return level_;
    }

    const int &xp() const
    {
        return xp_;
    }

    const double &attack() const
    {
        return attack_;
    }

    const double &defense() const
    {
        return defense_;
    }

    friend std::istream &operator>>(std::istream &i, PokemonDto &p);

    friend std::ostream &operator<<(std::ostream &o, const PokemonDto &p);
};

std::istream &operator>>(std::istream &i, PokemonDto &p)
{
    i >> p.name_;
    i >> p.nickname_;
    i >> p.primaryType_;
    i >> p.secondaryType_;
    i >> p.health_;
    i >> p.level_;
    i >> p.xp_;
    i >> p.attack_;
    return i >> p.defense_;
}

std::ostream &operator<<(std::ostream &o, const PokemonDto &p)
{
    return o << "name: " << p.name_ << " nickname: " << p.nickname_ << " level: " << p.level_ << " xp: " << p.xp_ << " attack: " << p.attack_ << " defense: " << p.defense_ << " primary type: " << p.primaryType_ << " secondary type: " << p.secondaryType_ << std::endl;
}