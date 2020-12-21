#ifndef POKEBAGITEM_HPP
#define POKEBAGITEM_HPP
#include <string.h>
#include <fstream>
class PokeBagItem
{
private:
  double price_;

public:
  PokeBagItem() { price_ = 0; }
  virtual void Use() = 0;
  virtual void format(std::ostream &out) const = 0;

  /*PokeBagItem(double price) : price_(price) {}
  double getPrice() {
      return price_;
  }*/

  friend std::ostream &operator<<(std::ostream &out, const PokeBagItem *temp) // bruger pointer for at dereferere objekt.
  {
    temp->format(out);
    out << "TEST";
    return out;
  }

  virtual ~PokeBagItem();
};

#endif