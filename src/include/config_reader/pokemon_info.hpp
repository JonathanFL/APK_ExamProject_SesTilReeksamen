#include <iostream>

class PokemonInfo
{
private:
    std::string  name_;
    std::string  primaryType_;
    std::string  secondaryType_;
    double health_;
    int level_;
    double attack_;
    double defense_;
    
public:
    PokemonInfo(const std::string &name, const std::string &nickname, const std::string &primaryType, const std::string &secondaryType, double health, int level, int xp, double attack, double defense)
    : name_(name), primaryType_(primaryType), secondaryType_(secondaryType), health_(health), level_(level), attack_(attack), defense_(defense)
    {
    }
    PokemonInfo():name_(""), primaryType_(""), secondaryType_(""), health_(0.0), level_(0), attack_(0.0), defense_(0.0){}

    friend std::istream &operator>>(std::istream &i, PokemonInfo &p);

    friend std::ostream &operator<<(std::ostream &o, const PokemonInfo &p);
};

std::istream &operator>>(std::istream &i, PokemonInfo &p)
{
    i >> p.name_;
    i >> p.primaryType_;
    i >> p.secondaryType_;
    i >> p.health_;
    i >> p.level_;
    i >> p.attack_;
    return i >> p.defense_;
}

std::ostream &operator<<(std::ostream &o, const PokemonInfo &p)
{
    return o << "name: " <<p.name_ << " level: " << p.level_ << " attack: "<< p.attack_ << " defense: " << p.defense_ << " primary type: "<< p.primaryType_ << " secondary type: "<< p.secondaryType_<< std::endl;
}