#ifndef _BATTLEGROUND_HPP_
#define _BATTLEGROUND_HPP_
#include "player.hpp"


class BattleGround {
public:
	Player playerOne;
	Player playerTwo;
	int currentPlayerPointer;
	static int step;
	static int turn;

private: 
	void makeСoordinatesCards(int centreX, int centreY, Player playerNumber);

public:
	void draw();
};




#endif