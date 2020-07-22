#ifndef _MENUBUTTONS_HPP_
#define _MENUBUTTONS_HPP_

#include "button.hpp"
#include <string>
#include <vector>

class TextButton : public Button
{
protected:
	std::string str;

public:
	void draw();
	TextButton(int x, int y, int w, int h, std::string s);
};

class CerberButton : public TextButton
{
public:
	void pressing();
	CerberButton(int x, int y, int w, int h);
};

class GameButton : public TextButton
{
public:
	void pressing();
	GameButton(int x, int y, int w, int h, std::string s);
};

class GamesWindow : public Button
{

};

#endif