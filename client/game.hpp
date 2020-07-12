#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "controlstate.hpp"

class Game : public ControlState
{
public:
	void update();
	void draw();
	void mousePress(int x, int y);
	void mouseRelease(int x, int y);
	Game(ControlState* parent);
};

#endif