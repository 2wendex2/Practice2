#include "game.hpp"
#include <iostream>
#include "../servercmd.hpp"

extern void writeMesg(int fd, const std::string& msg);
extern void gameEnd(int fd);

void Game::dispatchMsg(int player, std::string s)
{
	int pl2;
	if (player == player1)
		pl2 = player2;
	else
		pl2 = player1;
	msgSwitch(player, pl2, s);
}

void Game::msgSwitch(int player1, int player2, std::string s)
{
	Servercmd cmd(s);
	if (cmd[0] == "end")
	{
		gameEnd(player1);
		gameEnd(player2);
	}
}