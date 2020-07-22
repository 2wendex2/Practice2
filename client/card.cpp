#include "card.hpp"


void Card::PushCoordsCard(int centreX, int centreY, int dist) {
	this->x1 = centreX - this->r;
	this->x2 = centreX + this->r;
	this->y1 = centreY - this->R;
	this->y2 = centreY + this->R;
}