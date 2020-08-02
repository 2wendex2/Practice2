#ifndef _GAME_HPP_
#define _GAME_HPP_
#include "card.hpp"
#include <vector>
#include <iostream>

#include "controlstate.hpp"

class Game : public ControlState
{
private:
	std::vector<Card> player;
	std::vector<Card> enemyDeck;



private:
	void makeСoordinatesCards(int centreX, int centreY);

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