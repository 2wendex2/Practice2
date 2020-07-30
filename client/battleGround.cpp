#include "battleGround.hpp"
#include <glfw3.h>


void BattleGround::makeСoordinatesCards(int centreX, int centreY, Player playerNumber) {
	for (int i = 0; i < playerNumber.hand.size(); i++) {
		playerNumber.hand[i].pushCoordsCard(centreX, centreY);
		centreX += 2 * playerNumber.hand[i].r + 10;
	}	
}

void BattleGround::draw() {
	SpritePool::arena.draw(0, 0);
	BattleGround::makeСoordinatesCards(80, 470, this->playerOne);
	for (int i = 0; i < this->playerOne.hand.size(); i++) {
		this->playerOne.hand[i].draw();
	}
	BattleGround::makeСoordinatesCards(80, 130, this->playerTwo);
	for (int i = 0; i < this->playerTwo.hand.size(); i++) {
		this->playerTwo.hand[i].draw();
	}
}