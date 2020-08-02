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
		writeMesg(player2, "end\n");
	} else if (cmd[0] == "create") {
		
		if (this->player1 == player1) {
			std::string str = "card";
			for (int i = 0; i < 10; i++) {
				str += " " + std::to_string(this->playerOne.hand[i]);
			}
			str += "\n";
			writeMesg(player1, str);
		}
		else if (this->player2 == player1) {
			std::string str = "card";
			for (int i = 0; i < 10; i++) {
				str += " " + std::to_string(this->playerTwo.hand[i]);
			}
			str += "\n";
			writeMesg(player1, str);
		}
	}
	else if (cmd[0] == "click") {
		if (this->turn == 0 && this->player1 == player1) {
			std::string str = "throwcard";
			int index = std::stoi(cmd[1]);
			str += " " + std::to_string(this->playerOne.hand[index]);
			writeMesg(player1, str);
		}
		else if (this->turn == 1 && this->player2 == player1) {
			std::string str = "throwcard";
			int index = std::stoi(cmd[1]);
			str += " " + std::to_string(this->playerTwo.hand[index]);
			writeMesg(player1, str);
		}
	}

}