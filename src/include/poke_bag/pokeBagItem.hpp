#ifndef POKEBAGITEM_HPP
#define POKEBAGITEM_HPP
#include "../pokemon.hpp"
#include <iostream>
class IPokeBagItem
{
public:
	virtual void Use() = 0;
};

#endif