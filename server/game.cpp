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
		if (this->turn == 0) {
			if (this->player1 == player1 && this->step == 0) {
				std::string str1 = "attack";
				int ind = std::stoi(cmd[1]);
				this->index[0] = ind;
				if (!this->trueCard1[this->index[0]]) {
					return;
				}
				this->trueCard1[this->index[0]] = false;
				str1 += " " + std::to_string(this->playerOne.hand[this->index[0]]) + "\n";
				writeMesg(player1, str1);
				std::string str2 = "movecard";
				str2 += " " + std::to_string(this->index[0]) + " " + std::to_string(this->playerOne.hand[this->index[0]]) + "\n";
				writeMesg(player2, str2);
				this->step = 1;
			}
			else if (this->player2 == player1 && this->step == 1) {
				int k = 0;
				int powerAttack = this->playerOne.getPower(this->playerOne.hand[this->index[0]]);
				for (int i = 0; i < this->playerTwo.hand.size(); i++) {
					if ((this->playerTwo.getElement(this->playerTwo.hand[i]) == Card::Element::FIRE &&
						this->playerOne.getElement(this->playerOne.hand[this->index[0]]) == Card::Element::LAND) ||
						(this->playerTwo.getElement(this->playerTwo.hand[i]) == Card::Element::LAND &&
							this->playerOne.getElement(this->playerOne.hand[this->index[0]]) == Card::Element::AIR) ||
							(this->playerTwo.getElement(this->playerTwo.hand[i]) == Card::Element::AIR &&
								this->playerOne.getElement(this->playerOne.hand[this->index[0]]) == Card::Element::WATER) ||
								(this->playerTwo.getElement(this->playerTwo.hand[i]) == Card::Element::WATER &&
									this->playerOne.getElement(this->playerOne.hand[this->index[0]]) == Card::Element::FIRE)) {
						if (this->playerTwo.getPower(this->playerTwo.hand[i]) == powerAttack - 1 && this->trueCard2[i]) {
							k++;
						}
						else if (this->playerTwo.getPower(this->playerTwo.hand[i]) >= powerAttack && this->trueCard2[i]) {
							k++;
						}
					}
					else if (this->playerTwo.getPower(this->playerTwo.hand[i]) > powerAttack && this->trueCard2[i]) {
						k++;
					}
				}
				if (k == 0) {
					std::string str1 = "notcard\n";
					writeMesg(player1, str1);
					this->step = 0;
					this->turn = 1;
				}
				if (this->step == 1) {
					std::string str1 = "defence";
					int ind = std::stoi(cmd[1]);
					this->index[1] = ind;
					if (!this->trueCard2[this->index[1]]) {
						return;
					}
					if ((this->playerTwo.getElement(this->playerTwo.hand[this->index[1]]) == Card::Element::FIRE &&
						this->playerOne.getElement(this->playerOne.hand[this->index[0]]) == Card::Element::LAND) ||
						(this->playerTwo.getElement(this->playerTwo.hand[this->index[1]]) == Card::Element::LAND &&
							this->playerOne.getElement(this->playerOne.hand[this->index[0]]) == Card::Element::AIR) ||
							(this->playerTwo.getElement(this->playerTwo.hand[this->index[1]]) == Card::Element::AIR &&
								this->playerOne.getElement(this->playerOne.hand[this->index[0]]) == Card::Element::WATER) ||
								(this->playerTwo.getElement(this->playerTwo.hand[this->index[1]]) == Card::Element::WATER &&
									this->playerOne.getElement(this->playerOne.hand[this->index[0]]) == Card::Element::FIRE)) {
						if (this->playerTwo.getPower(this->playerTwo.hand[this->index[1]]) == powerAttack - 1) {
							str1 += " " + std::to_string(this->playerTwo.hand[this->index[1]]) + "\n";
						}
						else if (this->playerTwo.getPower(this->playerTwo.hand[this->index[1]]) >= powerAttack) {
							str1 += " " + std::to_string(this->playerTwo.hand[this->index[1]]) + "\n";
						}
					}
					else if (this->playerTwo.getPower(this->playerTwo.hand[this->index[1]]) > powerAttack) {
						str1 += " " + std::to_string(this->playerTwo.hand[this->index[1]]) + "\n";
					}
					if (str1.size() > 8) {
						int size = str1.size();
						this->trueCard2[this->index[1]] = false;
						writeMesg(player1, str1);
						std::string str2 = "movecard";
						str2 += " " + std::to_string(this->index[1]) + " " + std::to_string(this->playerTwo.hand[this->index[1]]) + "\n";
						writeMesg(player2, str2);
						this->step = 0;
						this->turn = 1;
					}
					else {
						std::string str2 = "weakcard\n";
						writeMesg(player1, str2);
					}
				}
			}
		}
		else if (this->turn == 1) {
			if (this->player2 == player1 && this->step == 0) {
				std::string str1 = "attack";
				int ind = std::stoi(cmd[1]);
				this->index[0] = ind;
				if (!this->trueCard2[ind]) {
					return;
				}
				this->trueCard2[ind] = false;
				str1 += " " + std::to_string(this->playerTwo.hand[this->index[0]]) + "\n";
				writeMesg(player1, str1);
				std::string str2 = "movecard";
				str2 += " " + std::to_string(this->index[0]) + " " + std::to_string(this->playerTwo.hand[this->index[0]]) + "\n";
				writeMesg(player2, str2);
				this->step = 1;
			}
			else if (this->player1 == player1 && this->step == 1) {
				int k = 0;
				if (!beatOffTheCard(this->index[0], this->playerOne, this->playerTwo)) {
					this->step = 0;
					this->turn = 0;
					std::string str1 = "notcard\n";
					writeMesg(player1, str1);
					return;
				}
				int powerAttack = this->playerTwo.getPower(this->playerTwo.hand[this->index[0]]);
				/*for (int i = 0; i < this->playerOne.hand.size(); i++) {
					if ((this->playerOne.getElement(this->playerOne.hand[i]) == Card::Element::FIRE &&
						this->playerTwo.getElement(this->playerTwo.hand[this->index[0]]) == Card::Element::LAND) ||
						(this->playerOne.getElement(this->playerOne.hand[i]) == Card::Element::LAND &&
							this->playerTwo.getElement(this->playerTwo.hand[this->index[0]]) == Card::Element::AIR) ||
							(this->playerOne.getElement(this->playerOne.hand[i]) == Card::Element::AIR &&
								this->playerTwo.getElement(this->playerTwo.hand[this->index[0]]) == Card::Element::WATER) ||
								(this->playerOne.getElement(this->playerOne.hand[i]) == Card::Element::WATER &&
									this->playerTwo.getElement(this->playerTwo.hand[this->index[0]]) == Card::Element::FIRE)) {
						if (this->playerOne.getPower(this->playerOne.hand[i]) == powerAttack - 1 && this->trueCard1[i]) {
							k++;
						}
						else if (this->playerOne.getPower(this->playerOne.hand[i]) >= powerAttack && this->trueCard1[i]) {
							k++;
						}
					}
					else if (this->playerOne.getPower(this->playerOne.hand[i]) > powerAttack && this->trueCard1[i]) {
						k++;
					}
				} 
				if (k == 0) {
					std::string str1 = "notcard\n";
					writeMesg(player1, str1);
					this->step = 0;
					this->turn = 0;
				} */
				if (this->step == 1) {
					std::string str1 = "defence";
					int ind = std::stoi(cmd[1]);
					this->index[1] = ind;
					if ((this->playerOne.getElement(this->playerOne.hand[this->index[1]]) == Card::Element::FIRE &&
						this->playerTwo.getElement(this->playerTwo.hand[this->index[0]]) == Card::Element::LAND) ||
						(this->playerOne.getElement(this->playerOne.hand[this->index[1]]) == Card::Element::LAND &&
							this->playerTwo.getElement(this->playerTwo.hand[this->index[0]]) == Card::Element::AIR) ||
							(this->playerOne.getElement(this->playerOne.hand[this->index[1]]) == Card::Element::AIR &&
								this->playerTwo.getElement(this->playerTwo.hand[this->index[0]]) == Card::Element::WATER) ||
								(this->playerOne.getElement(this->playerOne.hand[this->index[1]]) == Card::Element::WATER &&
									this->playerTwo.getElement(this->playerTwo.hand[this->index[0]]) == Card::Element::FIRE)) {
						if (this->playerOne.getPower(this->playerOne.hand[this->index[1]]) == powerAttack - 1) {
							str1 += " " + std::to_string(this->playerOne.hand[this->index[1]]) + "\n";
						}
						else if (this->playerOne.getPower(this->playerOne.hand[this->index[1]]) >= powerAttack) {
							str1 += " " + std::to_string(this->playerOne.hand[this->index[1]]) + "\n";
						}
					}
					else if (this->playerOne.getPower(this->playerOne.hand[this->index[1]]) > powerAttack) {
						str1 += " " + std::to_string(this->playerOne.hand[this->index[1]]) + "\n";
					}
					if (str1.size() > 8) {
						int size = str1.size();
						this->trueCard1[ind] = false;
						writeMesg(player1, str1);
						std::string str2 = "movecard";
						str2 += " " + std::to_string(this->index[1]) + " " + std::to_string(this->playerOne.hand[this->index[1]]) + "\n";
						writeMesg(player2, str2);
						this->turn = 0;
						this->step = 0;
					}
					else {
						std::string str2 = "weakcard\n";
						writeMesg(player1, str2);
					}
				}
			}
		}
	}
}

bool Game::beatOffTheCard(int id, Player& playerOne, Player& playerTwo) {
	int powerAttack = playerTwo.getPower(playerTwo.hand[id]);
	for (int i = 0; i < playerOne.hand.size(); i++) {
		if ((playerOne.getElement(playerOne.hand[i]) == Card::Element::FIRE &&
			playerTwo.getElement(playerTwo.hand[id]) == Card::Element::LAND) ||
			(playerOne.getElement(playerOne.hand[i]) == Card::Element::LAND &&
				playerTwo.getElement(playerTwo.hand[id]) == Card::Element::AIR) ||
				(playerOne.getElement(playerOne.hand[i]) == Card::Element::AIR &&
					playerTwo.getElement(playerTwo.hand[id]) == Card::Element::WATER) ||
					(playerOne.getElement(playerOne.hand[i]) == Card::Element::WATER &&
						playerTwo.getElement(playerTwo.hand[id]) == Card::Element::FIRE)) {
			if (playerOne.getPower(playerOne.hand[i]) == powerAttack - 1 && playerOne.trueCard[i]) {
				return true;
			}
			else if (playerOne.getPower(playerOne.hand[i]) >= powerAttack && playerOne.trueCard[i]) {
				return true;
			}
		}
		else if (playerOne.getPower(playerOne.hand[i]) > powerAttack && playerOne.trueCard[i]) {
			return true;
		}
	}
	return false;
}