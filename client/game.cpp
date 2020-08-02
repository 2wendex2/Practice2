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
	SpritePool::arena.draw(0, 0);
	for (int i = 0; i < this->player.size(); i++) {
		this->player[i].draw();
	}
	int x = 55;
	for (int i = 0; i < 10; i++) {
		SpritePool::rubashka.draw(x, 15);
		x += 70;
	}
	
	//Text::draw(760, 280, 800, 80, str, 20, 0.f, 0.7f, 1.f);
}

Game::Game(ControlState* parent) : ControlState(parent), player(10) {}

void Game::mousePress(int x, int y) {
	for (int i = 0; i < this->player.size(); i++) {
		if (this->player[i].x1 <= x && this->player[i].x2 >= x
			&& this->player[i].y1 <= y && this->player[i].y2 >= y) {
			std::string str = "click " + std::to_string(i) + "\n";
			settings.client.send_message(str.c_str());
		}
	}
}


void Game::charGet(char c) {}

void Game::makeСoordinatesCards(int centreX, int centreY) {
	for (int i = 0; i < this->player.size(); i++) {
		this->player[i].pushCoordsCard(centreX, centreY);
		centreX += 2 * 30 + 10;
	}
}

void Game::start() {
	settings.client.send_message("create\n");
	srand(time(0));
	Game::makeСoordinatesCards(85, 530);
	
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
				this->player[i].id = std::stoi(cmd[i + c + 1]);
			}
	
		}
		else if (cmd[c + 0] == "throwcard") {
			int index = std::stoi(cmd[c + 1]);
			this->player[index].pushCoordsCard(400, 300);
		}
		
	}
}