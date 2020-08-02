#ifndef _CARD_HPP_
#define _CARD_HPP_
#include <string>

class Card {
public:
	enum Element {
		FIRE,
		LAND,
		AIR,
		WATER
	};
	static const Element elementArray[16];
	static const int powerArray[16];
	
};

#endif