#include "card.hpp"


void Card::pushCoordsCard(int centreX, int centreY) {
	this->x1 = centreX - 30;
	this->x2 = centreX + 30;
	this->y1 = centreY - 60;
	this->y2 = centreY + 60;
}

void Card::draw() {
	SpritePool::cards[this->id].draw(this->x1, this->y1);
}



