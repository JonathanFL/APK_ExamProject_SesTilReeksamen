#ifndef POKEBAGITEM_HPP
#define POKEBAGITEM_HPP
#include <fstream>
#include <functional>
#include <string>
#include <variant>

#include "../pokemon/pokemon.hpp"

struct PokeBagItemResult
{
  std::string result;
};

class PokeBagItem
{

private:
  double              price_;
  std::string         type_;
  unsigned int        index_;
  static unsigned int indexCounter;

public:
  PokeBagItem()
  {
    index_ = indexCounter++;
    price_ = 0;
  }
  PokeBagItem(double price, std::string type) : price_(price), type_(type)
  {
    index_ = indexCounter++;
  }
  double      getPrice() { return price_; }
  void        setPrice(double price) { price_ = price; }
  std::string getType() { return type_; }
  void        setType(const std::string type) { type_ = type; }

  virtual void Use(Pokemon &                                  pokemon,
                   std::function<void(PokeBagItemResult res)> callback) = 0;
  virtual void format(std::ostream &out) const                          = 0;

  friend std::ostream &
  operator<<(std::ostream &out,
             const std::shared_ptr<PokeBagItem>
                 temp) // bruger pointer for at dereferere objekt
                       // yderligere efter derefereringen i Copy.
  {
    out << "[" << std::to_string(temp->index_) << "] ";
    temp->format(out);
    return out;
  }

  virtual ~PokeBagItem(){};
};

#endif