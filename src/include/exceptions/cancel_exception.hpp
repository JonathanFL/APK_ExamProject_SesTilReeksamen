#pragma once
#include <exception>
#include <string>
namespace exceptions
{

class ChoiceCancelledException : public std::exception
{
private:
  std::string choiceType_;

public:
  ChoiceCancelledException(std::string choiceType) : choiceType_("Choice of type " + choiceType + " cancled..."){};
  ~ChoiceCancelledException(){};

  virtual const char *what() const throw() { return choiceType_.c_str(); }
};

}