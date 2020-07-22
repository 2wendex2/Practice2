#include "battleGround.hpp"
#include <GLFW/glfw3.h>
void BattleGround::makeСoordinatesCards(int centreX, int centreY, Player playerNumber) {
	for (int i = 0; i < playerNumber.hand.size(); i++) {
		playerNumber.hand[i].PushCoordsCard(centreX, centreY, 10);
		centreX += 2 * playerNumber.hand[i].r + 10;
	}	
}

void BattleGround::drow() {
	BattleGround::makeСoordinatesCards(80, 470, BattleGround::playerOne);
	for (int i = 0; i < this->playerOne.hand.size(); i++) {
		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(this->playerOne.hand[i].x1, this->playerOne.hand[i].y1);
		glVertex2f(this->playerOne.hand[i].x2, this->playerOne.hand[i].y1);
		glVertex2f(this->playerOne.hand[i].x2, this->playerOne.hand[i].y2);
		glVertex2f(this->playerOne.hand[i].x1, this->playerOne.hand[i].y2);
		glEnd();
	}
	BattleGround::makeСoordinatesCards(80, 130, BattleGround::playerTwo);
	for (int i = 0; i < this->playerTwo.hand.size(); i++) {
		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(this->playerTwo.hand[i].x1, this->playerTwo.hand[i].y1);
		glVertex2f(this->playerTwo.hand[i].x2, this->playerTwo.hand[i].y1);
		glVertex2f(this->playerTwo.hand[i].x2, this->playerTwo.hand[i].y2);
		glVertex2f(this->playerTwo.hand[i].x1, this->playerTwo.hand[i].y2);
		glEnd();
	}

}