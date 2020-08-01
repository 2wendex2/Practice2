#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <event2/bufferevent.h>

class Game
{
	int player1;
	int player2;

	void msgSwitch(int player1, int player2, std::string s);
public:
	Game(int player1, int player2) : player1(player1), player2(player2) {}
	void dispatchMsg(int player, std::string s);
};

#endif // ! _GAME_HPP_
