#ifndef POKEBALL_HPP
#define POKEBALL_HPP
#include "ball.hpp"
#include <chrono>
#include <thread>

class PokeBall : public Ball
{
private:
  const double probabilityOfCatch = .50;
  const double levelPunishment    = .1;

public:
  PokeBall() {}
  void Catch(Pokemon &                                  pokemon,
             std::function<void(PokeBagItemResult res)> callback) override
  {
    std::cout << "Using PokeBall: probability of catching is "
              << 0.50_to_percent << "%" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    PokeBagItemResult res;
    if (pokemon.getLevel_() > 15)
    { // lower probability of catch if level if higher than 15
      res.result = caught(probabilityOfCatch - levelPunishment)
                       ? caughtSuccessMessage
                       : caughtFailMessage;
    }
    else
    {
      res.result =
          caught(probabilityOfCatch) ? caughtSuccessMessage : caughtFailMessage;
    }
    callback(res);
  }

  void formatImpl(std::ostream &out) const override { out << "Pokeball"; }
};
#endif