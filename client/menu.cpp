#include "menu.hpp"
#include "settings.hpp"
#include "textarea.hpp"
#include "control.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "text.hpp"
#include <iostream>

Menu::Menu(ControlState *parent) : ControlState(parent), newState(0), cb(16, 600 - 32, 256 - 32, 16), ngb(256, 600 -32, 
	256 - 64, 16), beg(0), prevButton(532, 600 - 32, 64, 16), nextButton(700, 600 - 32, 64, 16) {
}

void Menu::changeServer()
{
	newState = new TextArea(this, settings.host, "Enter host name", 17 * 24);
	Control::changeState(newState);
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
		//client->recreate(ip.c_str(), port.c_str());
		

		/*settings.client.recreate(ip.c_str(), port.c_str());
		if (!settings.client.valid())
			changeServer();
		else
			settings.client.send_message("UMAR_GAME CLIENT v.1");*/
	}
}

void Menu::newGame()
{
	GameButton gameButton(16, (gb.size() - beg) * 16 + 48, 800 - 32, 16);
	gb.push_back(gameButton);
	newState = new TextArea(this, gb[gb.size() -1].getStr(), "Enter game name", 24 * 2);
	Control::changeState(newState);
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