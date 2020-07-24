#ifndef _MENU_HPP_
#define _MENU_HPP_

#include <string>
#include <vector>
#include "controlstate.hpp"
#include "button.hpp"
#include "menubuttons.hpp"

class Menu : public ControlState
{
	ControlState* newState;
	CerberButton cb;
	NewGameButton ngb;
	NextButton nextButton;
	PrevButton prevButton;
	int beg;
	std::vector<GameButton> gb;
	static const int MAX_COUNT = 30;
	
public:
	void next();
	void prev();
	void changeServer();
	void newGame();
	void gameStart(std::string s);
	void draw();
	void start();
	void mouseMove(int x, int y);
	void mousePress(int x, int y);
	void mouseRelease(int x, int y);
	Menu(ControlState* parent);
};

#endif