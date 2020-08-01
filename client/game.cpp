#include <glfw3.h>
#include "game.hpp"
#include "spritepool.hpp"
#include <iostream>
#include "text.hpp"
#include <ctime>
#include <cstdlib>  
#include "settings.hpp"
#include <string>
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
	for (int i = 0; i < this->playerTwo.hand.size(); i++) {
		this->playerTwo.hand[i].draw();
	}
	Text::draw(760, 280, 800, 80, str, 20, 0.f, 0.7f, 1.f);
}

void Game::update() {}

Game::Game(ControlState* parent) : ControlState(parent) {}

void Game::mousePress(int x, int y) {	
	if (this->turn == 1) {
		for (int i = 0; i < this->playerOne.hand.size(); i++) {
			if (this->playerOne.hand[i].x1 <= x && this->playerOne.hand[i].x2 >= x
				&& this->playerOne.hand[i].y1 <= y && this->playerOne.hand[i].y2 >= y) {
				std::string str = "card " + std::to_string(i);
				settings.client.send_message(str.c_str());
			}
		}
	}
	if (this->turn == 2) {
		for (int i = 0; i < this->playerTwo.hand.size(); i++) {
			if (this->playerTwo.hand[i].x1 <= x && this->playerTwo.hand[i].x2 >= x
				&& this->playerTwo.hand[i].y1 <= y && this->playerTwo.hand[i].y2 >= y) {
				std::string str = "card " + std::to_string(i);
				settings.client.send_message(str.c_str());
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