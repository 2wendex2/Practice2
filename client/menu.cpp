#include "menu.hpp"
#include "settings.hpp"
#include "textarea.hpp"
#include "control.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "text.hpp"
#include <iostream>
#include "../servercmd.hpp"

Menu::Menu(ControlState *parent) : ControlState(parent), newState(0), cb(16, 600 - 32, 256 - 32, 16), ngb(256, 600 -32, 
	256 - 64, 16), beg(0), prevButton(532, 600 - 32, 64, 16), nextButton(700, 600 - 32, 64, 16) {
}

void Menu::changeServer()
{
	newState = new TextArea(this, settings.host, "Enter host name", 17 * 24);
	Control::changeState(newState);
	state = SERVER;
}

void Menu::gameStart(std::string s)
{
	newState = new Game(this);
	Control::changeState(newState);
}

void Menu::start()
{
	Graphics::changeBackgroundColor(0.f, 0.f, 0.f);
	if (newState != 0)
	{
		delete newState;
		settings.save();
	}
	if (state == SERVER)
		if (settings.host.length() == 0)
		{
			changeServer();
		}
		else
		{
			std::string ip = "";
			int i = 0;
			for (; i < settings.host.length() && settings.host[i] != ':'; i++)
				ip += settings.host[i];
			i++;
			std::string port = "";
			for (; i < settings.host.length(); i++)
				port += settings.host[i];

			std::cout << ip << ' ' << port << std::endl;

			tcp_client* client = new tcp_client;
			settings.client.recreate(ip.c_str(), port.c_str());

			settings.client.recreate(ip.c_str(), port.c_str());
			if (!settings.client.valid())
				changeServer();
			else
				settings.client.send_message("list");
		}
	else if (state == NEWGAME)
		{
			std::string s = "newgame ";
			s += lastGame;
			settings.client.send_message(s.c_str());
		}
}

void Menu::newGame()
{
	//GameButton gameButton(16, (gb.size() - beg) * 16 + 48, 800 - 32, 16);
	//gb.push_back(gameButton);
	lastGame = "";
	newState = new TextArea(this, lastGame, "Enter game name", 24 * 2);
	Control::changeState(newState);
	state = NEWGAME;
}

void Menu::addGame(std::string s)
{
	GameButton gameButton(16, (gb.size() - beg) * 16 + 48, 800 - 32, 16);
	gb.push_back(gameButton);
	gb[gb.size() - 1].getStr() = s;
}

void Menu::deleteGame(std::string s)
{
	int i = 0;
	for (; gb[i].getStr() != s && i < gb.size(); i++);
	if (i == gb.size())
		return;
	gb.erase(gb.begin() + i);
	for (; i < gb.size(); i++)
		gb[i].next();
}

void Menu::draw()
{
	cb.draw();
	ngb.draw();
	for (int i = beg; i < gb.size() && i < beg + MAX_COUNT; i++)
		gb[i].draw();
	if (beg > 0)
		prevButton.draw();
	if (beg + MAX_COUNT < gb.size())
		nextButton.draw();
	Text::draw(400,600 - 48, 800, 16, settings.host, 16, 1.f, 1.f, 0.f);
	Text::draw(400, 16, 800, 32, "Select game", 32, 0.f, 0.7f, 1.f);
}

void Menu::mouseMove(int x, int y)
{
	cb.move(x, y);
	ngb.move(x, y);
	for (int i = beg; i < gb.size() && i < beg + MAX_COUNT; i++)
		gb[i].move(x, y);
	if (beg > 0)
		prevButton.move(x, y);
	if (beg + MAX_COUNT < gb.size())
		nextButton.move(x, y);
}

void Menu::mousePress(int x, int y)
{
	cb.press(x, y);
	ngb.press(x, y);
	for (int i = beg; i < gb.size() && i < beg + MAX_COUNT; i++)
		gb[i].press(x, y);
	if (beg > 0)
		prevButton.press(x, y);
	if (beg + MAX_COUNT < gb.size())
		nextButton.press(x, y);
}

void Menu::mouseRelease(int x, int y)
{
	cb.release(x, y);
	ngb.release(x, y);
	for (int i = beg; i < gb.size() && i < beg + MAX_COUNT; i++)
		gb[i].release(x, y);
	if (beg > 0)
		prevButton.release(x, y);
	if (beg + MAX_COUNT < gb.size())
		nextButton.release(x, y);
}

void Menu::prev()
{
	beg--;
	for (int i = 0; i < gb.size(); i++)
		gb[i].prev();
}

void Menu::next()
{
	beg++;
	for (int i = 0; i < gb.size(); i++)
		gb[i].next();
}

void Menu::update()
{
	for (;;)
	{
		std::string cmdstring = settings.client.recieve_message();
		if (cmdstring.size() == 0)
			break;

		Servercmd cmd(cmdstring);
		if (cmd[0] == "list" && cmd[1].size() != 0)
			addGame(cmd[1]);
		else if (cmd[0] == "relist")
		{
			gb.clear();
			beg = 0;
		}
		else if (cmd[0] == "delete")
			deleteGame(cmd[1]);
	}
}