﻿#ifndef _GAME_HPP_
#define _GAME_HPP_
#include "player.hpp"

#include "controlstate.hpp"

class Game : public ControlState
{
private:
	std::vector<Card> table;
	Player playerOne;
	Player playerTwo;
	std::vector<int> index;
	int currentPlayerPointer;
	static int step;
	int turn;

private:
	void makeСoordinatesCards(int centreX, int centreY, Player& playerNumber);

public:
	void update();
	void draw();
	void mousePress(int x, int y);
	void charGet(char c);
	void keyGet(int key);
	Game(ControlState* parent);
	void start();
};

#endif