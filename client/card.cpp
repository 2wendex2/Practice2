#include "card.hpp"


void Card::PushCoordsCard(int centreX, int centreY, int dist) {
	this->x1 = centreX - this->r;
	this->x2 = centreX + this->r;
	this->y1 = centreY - this->R;
	this->y2 = centreY + this->R;
}

std::string Card::pickTexture(Card card) {
	switch (card.id)
	{
	case 1:
		card.texture = "1.png";
		break;
	case 2:
		card.texture = "2.png";
		break;
	case 3:
		card.texture = "3.png";
		break;
	case 4:
		card.texture = "4.png";
		break;
	case 5:
		card.texture = "5.png";
		break;
	case 6:
		card.texture = "6.png";
		break;
	case 7:
		card.texture = "7.png";
		break;
	case 8:
		card.texture = "8.png";
		break;
	case 9:
		card.texture = "9.png";
		break;
	case 10:
		card.texture = "10.png";
		break;
	case 11:
		card.texture = "11.png";
		break;
	case 12:
		card.texture = "12.png";
		break;
	case 13:
		card.texture = "13.png";
		break;
	case 14:
		card.texture = "14.png";
		break;
	case 15:
		card.texture = "15.png";
		break;
	case 16:
		card.texture = "16.png";
		break;

	default:
		card.texture = "error";
		break;
	}
	return card.texture;
}