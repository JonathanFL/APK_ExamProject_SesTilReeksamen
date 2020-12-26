#pragma once
#include <exception>
#include <string>
class ChoiceCancledException : public std::exception
{
private:
  std::string choiceType_;

public:
  ChoiceCancledException(std::string choiceType) : choiceType_("Choice of type " + choiceType + " cancled..."){};
  ~ChoiceCancledException(){};

  virtual const char *what() const throw() { return choiceType_.c_str(); }
};
