#ifndef _GAMEWAITING_HPP_
#define _GAMEWAITING_HPP_

#include "controlstate.hpp"

class GameWaiting : public ControlState
{
public:
	void update();
	void draw();
	void keyGet(int key);
	GameWaiting(ControlState* parent);
};

#endif