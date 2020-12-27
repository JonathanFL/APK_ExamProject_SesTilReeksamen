#ifndef ATTACK_HPP
#define ATTACK_HPP

template <typename T>
class Attack
{
private:
  T attacker_;

public:
  Attack(T &attacker) : attacker_(attacker) {}
  template <typename T1 = T>
  typename std::enable_if<IsSame<T1, Pokemon>::value, std::string>::type
  doAttack(Pokemon &p)
  {
    double modifier = attacker_.getModifier(p);
    double currentHealth = p.getHealth_();
    double damage = attacker_.getAttack_() * modifier;
    currentHealth -= damage;
    if (currentHealth < 0)
      currentHealth = 0;
    p.setHealth_(currentHealth);
    std::string effectiveness;
    if (modifier < 0.5)
    {
      effectiveness = "It was very ineffective";
    }
    else if (modifier < 1)
    {
      effectiveness = "It was not very effective";
    }
    else if (modifier > 1)
    {
      effectiveness = "It was very effective";
    }
    else if (modifier > 1.5)
    {
      effectiveness = "It was super effective";
    }

    std::string fainted;
    if (p.getHealth_() == 0)
    {
      fainted = (p.getNickname_().empty() ? p.getName_() : p.getNickname_()) + " fainted...\n";
    }

    if (p.getNickname_().empty())
    {
      return attacker_.getNickname_() + " attacked wild " + p.getName_() +
             " for " + std::to_string(damage) + "\n" + effectiveness + "\n" + fainted;
    }
    return "Wild " + attacker_.getName_() + " attacked " + p.getNickname_() +
           " for " + std::to_string(damage) + "\n" + effectiveness + "\n" + fainted;
  }

  template <typename T1 = T>
  typename std::enable_if<std::is_base_of<Ball, T1>::value, bool>::type
  doAttack(Pokemon &p)
  {
  }
};

#endif