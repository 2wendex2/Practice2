#ifndef _CARD_HPP_
#define _CARD_HPP_
#include <string>
#include"spritepool.hpp"

class Card {
public:
	std::string element;
	std::string name;
	int power;
	int id;
	int x1, y1, x2, y2;
	int r = 30, R = 60;

	Card(std::string name, std::string element, int power, int id) {
		this->name = name;
		this->element = element;
		this->power = power;
		this->id = id;
	}

public:
	void pushCoordsCard(int centreX, int centreY);
	void draw();
	void getCard(int x, int y);
};

#endif