#ifndef _BATTLEGROUND_HPP_
#define _BATTLEGROUND_HPP_
#include "player.hpp"


class BattleGround {
public:
	Player playerOne, playerTwo;
	int currentPlayerPointer;

private: 
	void makeСoordinatesCards(int centreX, int centreY, Player playerNumber);

public:
	void drow();
};




#endif