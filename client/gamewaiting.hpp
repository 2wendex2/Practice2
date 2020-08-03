#ifndef _GAMEWAITING_HPP_
#define _GAMEWAITING_HPP_

#include "controlstate.hpp"
#include <string>

class GameWaiting : public ControlState
{
	std::string s;
public:
	void update();
	void draw();
	void keyGet(int key);
	GameWaiting(ControlState* parent, const std::string &s);
};

#endif