#ifndef BATTLECRY_HPP
#define BATTLECRY_HPP
#include "boost/signals2.hpp"
template <typename T> class PrintContainer
{
public:
  typedef T value_type;
  using iterator = typename std::back_insert_iterator<PrintContainer>;
  void push_back(const T &value) { std::cout << value << std::endl; }
};

template <typename Container> struct aggregate_output
{
  typedef Container result_type;

  template <typename InputIterator>
  Container operator()(InputIterator first, InputIterator last) const
  {
    Container                    c;
    typename Container::iterator it(c);
    std::copy(first, last, it);
    return c;
  }
};
typedef boost::signals2::signal<std::string(),
                                aggregate_output<PrintContainer<std::string>>>
                                   BattleCrySignal;
typedef BattleCrySignal::slot_type BattleCrySlot;
class BattleCry
{
private:
  BattleCrySignal battleCrySignal_;

public:
  void add(const BattleCrySlot &cb) { battleCrySignal_.connect(cb); }
  void operator()() { battleCrySignal_(); }
};

#endif