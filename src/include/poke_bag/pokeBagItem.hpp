#ifndef POKEBAGITEM_HPP
#define POKEBAGITEM_HPP
#include<string> 
#include <fstream>
#include <functional>
#include <variant>

struct PokeBagItemResult
{
  std::string result;
};

class PokeBagItem
{
  static unsigned int indexCounter;
private:
  double price_;

public:
  PokeBagItem(){index_ = indexCounter++; price_ = 0;}
  unsigned int index_;

  PokeBagItem(double price) : price_(price) {index_ = indexCounter++;}
  
  double getPrice() {
      return price_;
  }

  virtual void Use(std::function<void(PokeBagItemResult res)> callback) = 0;
  virtual void format(std::ostream &out) const = 0;
  

  friend std::ostream& operator<<(std::ostream& out, const PokeBagItem* temp)// bruger pointer for at dereferere objekt yderligere efter derefereringen i Copy.
  {
    out << "[" << std::to_string(temp->index_) << "] ";
    temp->format(out);
    return out;
  }

  virtual ~PokeBagItem();
};

#endif