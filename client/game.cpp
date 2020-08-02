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
#include <vector>;

void Game::keyGet(int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		settings.client.send_message("end\n");
		Control::changeState(parent);
	}
}

void Game::draw() {
	SpritePool::arena.draw(0, 0);
	for (int i = 0; i < this->hand.size(); i++) {
		this->hand[i].draw();
	}
	int x = 55;
	for (int i = 0; i < this->enemyDeck.size(); i++) {
		this->enemyDeck[i].draw();
	}
	
	//Text::draw(760, 280, 800, 80, str, 20, 0.f, 0.7f, 1.f);
}

Game::Game(ControlState* parent) : ControlState(parent), hand(10), enemyDeck(10) {}

void Game::mousePress(int x, int y) {
	for (int i = 0; i < this->hand.size(); i++) {
		if (this->hand[i].x1 <= x && this->hand[i].x2 >= x
			&& this->hand[i].y1 <= y && this->hand[i].y2 >= y) {
			std::string str = "click " + std::to_string(i) + "\n";
			settings.client.send_message(str.c_str());
		}
	}
}


void Game::charGet(char c) {}

void Game::makeСoordinatesCards(int centreX, int centreY, std::vector<Card>& deck) {
	for (int i = 0; i < deck.size(); i++) {
		deck[i].id = 16;
		deck[i].pushCoordsCard(centreX, centreY);
		centreX += 70;
	}
}

void Game::start() {
	settings.client.send_message("create\n");
	srand(time(0));
	Game::makeСoordinatesCards(85, 530, this->hand);
	Game::makeСoordinatesCards(85, 75, this->enemyDeck);
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
		} else if (cmd[c + 0] == "card") {

			for (int i = 0; i < 10; i++) {
				this->hand[i].id = std::stoi(cmd[i + c + 1]);
			}
	
		} else if (cmd[c + 0] == "attack1") {
			int index = std::stoi(cmd[c + 1]);
			for (int i = 0; i < this->hand.size(); i++) {
				if (this->hand[i].id == index) {
					this->hand[i].pushCoordsCard(400, 370);
					break;
				}
			}
		}
		else if (cmd[c + 0] == "movecard1") {
			int index = std::stoi(cmd[c + 1]);
			int id = std::stoi(cmd[c + 2]);
			this->enemyDeck[index].pushCoordsCard(400, 230);
			this->enemyDeck[index].id = id;
		}
		else if (cmd[c + 0] == "defence1") {
			int index = std::stoi(cmd[c + 1]);
			for (int i = 0; i < this->hand.size(); i++) {
				if (this->hand[i].id == index) {
					this->hand[i].pushCoordsCard(400, 370);
					break;
				}
			}
		} else if (cmd[c + 0] == "movecard2") {
			int index = std::stoi(cmd[c + 1]);
			int id = std::stoi(cmd[c + 2]);
			this->enemyDeck[index].pushCoordsCard(400, 230);
			this->enemyDeck[index].id = id;
		}
	}
}