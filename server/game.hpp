#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <event2/bufferevent.h>
#include "player.hpp"

class Game {	
	Player  playerOne;
	Player  playerTwo;
	int player1;
	int player2;
	std::vector<int> deckPlayer;
	int turn;
	int step = 0;
	std::vector<int> index;

	bool beatOffTheCard(int id, Player& playerOne, Player& playerTwo);
	void gameCompleted();
	int checkHand(Player& player);

	void msgSwitch(int player1, int player2, std::string s);
public:
	Game(int player1, int player2) : player1(player1), player2(player2), index(2), turn(rand() % 2) {}
	void dispatchMsg(int player, std::string s);

};

#endif // ! _GAME_HPP_
