#include <glfw3.h>
#include "game.hpp"
#include "spritepool.hpp"
#include <iostream>
#include "text.hpp"
#include <ctime>
#include <cstdlib>  
#include "settings.hpp"
#include <string>
#include "../servercmd.hpp"
#include "control.hpp"

void Game::keyGet(int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		settings.client.send_message("end\n");
		Control::changeState(parent);
	}
}

void Game::draw() {
	std::string str = std::to_string(playerOne.getScore()) + "-" + std::to_string(playerTwo.getScore());
	SpritePool::arena.draw(0, 0);
	for (int i = 0; i < this->playerOne.hand.size(); i++) {
		this->playerOne.hand[i].draw();
	}
	for (int i = 0; i < this->table.size(); i++) {
		this->table[i].draw();
	}
	for (int i = 0; i < this->playerTwo.hand.size(); i++) {
		this->playerTwo.hand[i].draw();
	}
	Text::draw(760, 280, 800, 80, str, 20, 0.f, 0.7f, 1.f);
}

Game::Game(ControlState* parent) : ControlState(parent) {}

void Game::mousePress(int x, int y) {
	this->turn = 1;
	if (Game::turn == 1) {
		for (int i = 0; i < this->playerOne.hand.size(); i++) {
			if (this->playerOne.hand[i].x1 <= x && this->playerOne.hand[i].x2 >= x 
				&& this->playerOne.hand[i].y1 <= y && this->playerOne.hand[i].y2 >= y) {
				this->table.push_back(this->playerOne.hand[i]);
				for (int j = 0; j < this->table.size(); j++) {
					this->table[j].pushCoordsCard(400, 300);
				}
				this->playerOne.hand.erase(this->playerOne.hand.begin() + i);
				break;
			}
		}
	}
}

void Game::charGet(char c) {}

void Game::makeСoordinatesCards(int centreX, int centreY, Player& playerNumber) {
	for (int i = 0; i < playerNumber.hand.size(); i++) {
		playerNumber.hand[i].pushCoordsCard(centreX, centreY);
		centreX += 2 * playerNumber.hand[i].r + 10;
	}
}

void Game::start() {
	srand(time(0));

	Game::makeСoordinatesCards(85, 530, this->playerOne);
	Game::makeСoordinatesCards(85, 75, this->playerTwo);
	
}

void Game::update()
{
	std::string cmdstring = settings.client.recieve_message();
	if (cmdstring.size() == 0)
		return;

	Servercmd cmd(cmdstring);
	for (int c = 0; c < cmd.size(); c++)
	{
		if (cmd[c + 0] == "end")
		{
			Control::changeState(parent);
			break;
		}
	}
}