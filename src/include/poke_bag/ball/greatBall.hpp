#ifndef GREATBALL_HPP
#define GREATBALL_HPP
#include "ball.hpp"
#include <chrono>
#include <thread>

class GreatBall : public Ball
{
private:
  const double probabilityOfCatch = .75;
  const double levelPunishment    = .1;

public:
  GreatBall() {}
  void Catch(Pokemon &                                  pokemon,
             std::function<void(PokeBagItemResult res)> callback) override
  {
    std::cout << "Using GreatBall: probability of catching is "
              << 0.75_to_percent << "%" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    PokeBagItemResult res;
    if (pokemon.getLevel_() > 25)
    { // lower probability of catch if level if higher than 25
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

  void formatImpl(std::ostream &out) const override { out << "Greatball"; }
};
#endif