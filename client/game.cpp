#include "game.hpp"
#include "spritepool.hpp"
#include <iostream>
#include "text.hpp"
#include <ctime>
#include <cstdlib>  



void Game::draw() {
	SpritePool::arena.draw(0, 0);
	for (int i = 0; i < this->playerOne.hand.size(); i++) {
		this->playerOne.hand[i].draw();
	}
	for (int i = 0; i < this->playerTwo.hand.size(); i++) {
		this->playerTwo.hand[i].draw();
	}
}

void Game::update() {}

Game::Game(ControlState* parent) : ControlState(parent) {}

void Game::mousePress(int x, int y) {
	this->turn = 1;
	if (Game::turn == 1) {
		for (int i = 0; i < this->playerOne.hand.size(); i++) {
			this->playerOne.hand[i].getCard(x, y);
		}
	}
}


void Game::mouseRelease(int x, int y) { std::cout << x << ' ' << y << ' ' << "LUPA" << std::endl; }
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