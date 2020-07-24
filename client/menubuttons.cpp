#include "menubuttons.hpp"
#include "control.hpp"
#include "menu.hpp"
#include "text.hpp"
#include <iostream>

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

GameButton::GameButton(int x, int y, int w, int h) : TextButton(x, y, w, h, "") {}

std::string& GameButton::getStr()
{
	return str;
}

void GameButton::pressing()
{
	((Menu*)Control::getState())->gameStart(str);
}

NewGameButton::NewGameButton(int x, int y, int w, int h) : TextButton(x, y, w, h, "New game") {}

void NewGameButton::pressing()
{
	((Menu*)Control::getState())->newGame();
}

NextButton::NextButton(int x, int y, int w, int h) : TextButton(x, y, w, h, "Next") {}

void NextButton::pressing()
{
	((Menu*)Control::getState())->next();
}

PrevButton::PrevButton(int x, int y, int w, int h) : TextButton(x, y, w, h, "Prev") {}

void PrevButton::pressing()
{
	((Menu*)Control::getState())->prev();
}

void GameButton::prev()
{
	y += 16;
}

void GameButton::next()
{
	y -= 16;
}