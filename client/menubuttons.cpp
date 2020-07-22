#include "menubuttons.hpp"
#include "control.hpp"
#include "menu.hpp"
#include "text.hpp"

TextButton::TextButton(int x, int y, int w, int h, std::string s) : Button(x, y, w, h), str(s) {}

void TextButton::draw()
{
	int tx = x + w / 2, ty = y + h / 2;

	if (pressed)
		Text::draw(tx, ty, w, h, str, 16, 1.f, 0.f, 0.f);
	else if (moved)
		Text::draw(tx, ty, w, h, str, 16, 0.f, 1.f, 0.f);
	else
		Text::draw(tx, ty, w, h, str, 16, 1.f, 1.f, 1.f);
}

void CerberButton::pressing()
{
	((Menu*)Control::getState())->changeServer();
}

CerberButton::CerberButton(int x, int y, int w, int h) : TextButton(x, y, w, h, "Change cerber") {}

GameButton::GameButton(int x, int y, int w, int h, std::string s) : TextButton(x, y, w, h, s) {}

void GameButton::pressing()
{
	((Menu*)Control::getState())->gameStart(str);
}