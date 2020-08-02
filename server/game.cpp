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
	std::cout << this->turn << std::endl;
	Servercmd cmd(s);
	if (cmd[0] == "end")
	{
		gameEnd(player1);
		gameEnd(player2);
		writeMesg(player2, "end\n");
	}
	else if (cmd[0] == "create") {

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
		this->turn == 0;
		if (this->turn == 0) {
			if (this->player1 == player1 && this->step == 0) {
				std::string str1 = "attack";
				int index = std::stoi(cmd[1]);
				str1 += " " + std::to_string(this->playerOne.hand[index]);
				writeMesg(player1, str1);
				std::string str2 = "movecard1";
				str2 += " " + std::to_string(index) + " " + std::to_string(this->playerOne.hand[index]);
				writeMesg(player2, str2);
				this->step++;
			}
			else if (this->player2 == player1 && this->step == 1) {
				int index = std::stoi(cmd[1]);
				std::string str2 = "movecard2";
				str2 += " " + std::to_string(this->playerTwo.hand[index]);
				writeMesg(player2, str2);
			}
		}
		else if (this->turn == 1 && this->player2 == player1) {
			std::string str = "attack";
			int index = std::stoi(cmd[1]);
			str += " " + std::to_string(this->playerTwo.hand[index]);
			writeMesg(player1, str);
		}
	}
}