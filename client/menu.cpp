#include "menu.hpp"
#include "settings.hpp"
#include "textarea.hpp"
#include "control.hpp"
#include "graphics.hpp"
#include "game.hpp"

Menu::Menu(ControlState *parent) : ControlState(parent), newState(0), cb(16, 600 - 32, 256 - 32, 16), gb(16, 100, 256 -32, 16,
	"PINGAS") {}

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
}

void Menu::draw()
{
	cb.draw();
	gb.draw();
}

void Menu::mouseMove(int x, int y)
{
	cb.move(x, y);
	gb.move(x, y);
}

void Menu::mousePress(int x, int y)
{
	cb.press(x, y);
	gb.press(x, y);
}

void Menu::mouseRelease(int x, int y)
{
	cb.release(x, y);
	gb.release(x, y);
}