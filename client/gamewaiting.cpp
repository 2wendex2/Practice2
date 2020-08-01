#include "gamewaiting.hpp"
#include "spritepool.hpp"
#include <iostream>
#include "text.hpp"
#include "settings.hpp"
#include "game.hpp"
#include "control.hpp"
#include "menu.hpp"
#include "../servercmd.hpp"
#include <glfw3.h>

void GameWaiting::draw()
{
	Text::draw(400, 300, 800, 600, "Waiting  forplayer", 64, 0.f, 0.7f, 1.f);
}

void GameWaiting::keyGet(int key)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		settings.client.send_message("exit\n");
		Control::changeState(parent);
	}
}

void GameWaiting::update()
{
	std::string cmdstring = settings.client.recieve_message();
	if (cmdstring.size() == 0)
		return;

	Servercmd cmd(cmdstring);
	for (int c = 0; c < cmd.size(); c++)
	{
		if (cmd[c + 0] == "start")
		{
			((Menu*)parent)->changeState(new Game(parent));
			return;
		}
	}
}

GameWaiting::GameWaiting(ControlState* parent) : ControlState(parent) {}
