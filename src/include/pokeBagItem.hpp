#ifndef POKEBAGITEM_HPP
#define POKEBAGITEM_HPP
class PokeBagItem
{
private:
  double price_;

public:
  PokeBagItem(double price) : price_(price) {}
  double getPrice() {
      return price_;
  }
};
#endif