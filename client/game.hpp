#ifndef _GAME_HPP_
#define _GAME_HPP_
#include "card.hpp"
#include <vector>
#include <iostream>

#include "controlstate.hpp"

class Game : public ControlState
{
private:
	std::vector<Card> hand;
	std::vector<Card> enemyDeck;
	Card* myCard = NULL;
	Card* enemyCard = NULL;
	int score1 = 0;
	int score2 = 0;
	std::string str;
	int x = 100;
	bool draw_Text = false;


private:
	void makeСoordinatesCards(int centreX, int centreY, std::vector<Card>& deck);

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