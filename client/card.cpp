#include "card.hpp"


void Card::pushCoordsCard(int centreX, int centreY) {
	this->x1 = centreX - this->r;
	this->x2 = centreX + this->r;
	this->y1 = centreY - this->R;
	this->y2 = centreY + this->R;
}

void Card::drawMyDeck() {
	SpritePool::cards[this->id].draw(this->x1, this->y1);
}

void Card::drawYourDeck() {
	SpritePool::rubashka.draw(this->x1, this->y1);
}

void Card::getCard(int x, int y) {
	if (this->x1 <= x && this->x2 >= x && this->y1 <= y && this->y2 >= y) {
		this->x1 = 330;
		this->y1 = 290;
	}
}