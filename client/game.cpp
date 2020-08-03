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
#include <chrono>
#include <thread>


void Game::keyGet(int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		settings.client.send_message("end\n");
		Control::changeState(parent);
	}
}

void Game::draw() {
	std::string str1 = std::to_string(this->score1);
	std::string str2 = std::to_string(this->score2);
	SpritePool::arena.draw(0, 0);
	for (int i = 0; i < this->hand.size(); i++) {
		this->hand[i].draw();
	}
	for (int i = 0; i < this->enemyDeck.size(); i++) {
		this->enemyDeck[i].draw();
	}
	Text::draw(this->x, 320, 800, 80, this->str, 20, 0.f, 0.7f, 1.f);
	Text::draw(720, 400, 800, 80, str1, 20, 0.f, 0.7f, 1.f);
	Text::draw(720, 200, 800, 80, str2, 20, 0.f, 0.7f, 1.f);
}

Game::Game(ControlState* parent) : ControlState(parent), hand(10), enemyDeck(10) {}

void Game::mousePress(int x, int y) {
	for (int i = 0; i < this->hand.size(); i++) {
		if (this->hand[i].x1 <= x && this->hand[i].x2 >= x
			&& this->hand[i].y1 <= y && this->hand[i].y2 >= y && this->hand[i].clickable == true) {
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
	
		} else if (cmd[c + 0] == "attack") {
			this->x = 100;
			this->str = "enemy move";
			if (this->myCard != NULL) {
				this->myCard->putOnTexture = false;
				this->myCard = NULL;
			}
			if (this->enemyCard != NULL) {
				this->enemyCard->putOnTexture = false;
				this->enemyCard = NULL;
			}
			int index = std::stoi(cmd[c + 1]);
			for (int i = 0; i < this->hand.size(); i++) {
				if (this->hand[i].id == index) {
					this->hand[i].pushCoordsCard(400, 370);
					this->myCard = &this->hand[i];
					this->hand[i].clickable = false;
					break;
				}
			}
		}
		else if (cmd[c + 0] == "movecard") {
			this->x = 100;
			if (this->enemyCard != NULL) {
				if (this->myCard != NULL) {
					this->myCard->putOnTexture = false;
					this->myCard = NULL;
				}
				if (this->enemyCard != NULL) {
					this->enemyCard->putOnTexture = false;
					this->enemyCard = NULL;
				}
			}
			if (this->myCard == NULL) {
				this->str = "your move";
			}
			else {
				this->str = "enemy move";
			}
			int index = std::stoi(cmd[c + 1]);
			int id = std::stoi(cmd[c + 2]);
			this->enemyDeck[index].pushCoordsCard(400, 230);
			this->enemyDeck[index].id = id;
			this->enemyCard = &this->enemyDeck[index];
		}
		else if (cmd[c + 0] == "defence") {
			this->x = 100;
			this->str = "your move";
			int index = std::stoi(cmd[c + 1]);
			for (int i = 0; i < this->hand.size(); i++) {
				if (this->hand[i].id == index) {
					this->hand[i].pushCoordsCard(400, 370);
					this->myCard = &this->hand[i];
					this->hand[i].clickable = false;
					break;
				}
			}
		} 
		else if (cmd[c + 0] == "weakcard") {
			this->x = 100;
			this->str = "weak card";
		}
		else if (cmd[c + 0] == "notcard") {
			this->score2++;
			this->str = "no cards to defence";
			this->x = 200;
		}
		else if (cmd[c + 0] == "score") {
			this->score1++;
			this->x = 100;
			this->str = "enemy move";
			this->enemyCard = this->myCard;
		}
		else if (cmd[c + 0] == "turn") {
			this->x = 100;
			this->str = "your move";
		}
		else if (cmd[c + 0] == "noturn") {
			this->x = 100;
			this->str = "enemy move";
		}
		else if (cmd[c + 0] == "win") {
			this->x = 100;
			this->str = "YOU WIN";
		}
		else if (cmd[c + 0] == "lose") {
			this->x = 100;
			this->str = "YOU LOSE";
		}
		else if (cmd[c + 0] == "draw") {
			this->x = 100;
			this->str = "DRAW";
		}
	}
}