#ifndef BALL_HPP
#define BALL_HPP
#include "../pokeBagItem.hpp"
#include <iostream>
#include <random>
#include <string>

constexpr long double operator"" _to_percent(long double input)
{
  return input * 100;
}

class Ball : public PokeBagItem
{
public:
  Ball() : PokeBagItem() {}
  const std::string caughtSuccessMessage = "You caught the Pokemon\n";
  const std::string caughtFailMessage    = "You did NOT catch the Pokemon\n";
  bool              caught(double probabilityOfCatch)
  {
    std::random_device                     rd;
    std::uniform_real_distribution<double> distribution(0, 1);
    std::mt19937 engine(rd()); // Mersenne twister MT19937

    double value = distribution(engine);
    return value < probabilityOfCatch;
  };

  void Use(Pokemon &                                  pokemon,
           std::function<void(PokeBagItemResult res)> callback) override
  {
    Catch(pokemon, callback);
  }
  void format(std::ostream &out) const override { this->formatImpl(out); }

  virtual void formatImpl(std::ostream &out) const = 0;

  virtual void Catch(Pokemon &                                  pokemon,
                     std::function<void(PokeBagItemResult res)> callback) = 0;

  virtual ~Ball();

private:
};

#endif