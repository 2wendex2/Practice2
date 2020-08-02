#ifndef _CARD_HPP_
#define _CARD_HPP_
#include <string>
#include"spritepool.hpp"

class Card {
public:
	int id;
	int x1, y1, x2, y2;
	int r = 30, R = 60;


public:
	void pushCoordsCard(int centreX, int centreY);
	void draw();
};

#endif