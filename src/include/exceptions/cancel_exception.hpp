#pragma once
#include <exception>
#include <string>
class ChoiceCancledException : public std::exception
{
private:
  std::string choiceType_;

public:
  ChoiceCancledException(std::string choiceType) : choiceType_(choiceType){};
  ~ChoiceCancledException(){};

  virtual const char *what() const throw() { return "Choice of type " + choiceType_ + " cancled..."; }
};
