#ifndef _GAME_HPP_
#define _GAME_HPP_
#include "player.hpp"

#include "controlstate.hpp"

class Game : public ControlState
{
private:
	Player playerOne;
	Player playerTwo;
	int currentPlayerPointer;
	static int step;
	int turn;

private:
	void makeСoordinatesCards(int centreX, int centreY, Player& playerNumber);

public:
	void update();
	void draw();
	void mousePress(int x, int y);
	void mouseRelease(int x, int y);
	void charGet(char c);
	Game(ControlState* parent);
	void start();
};

#endif