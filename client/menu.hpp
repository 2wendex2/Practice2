#ifndef _MENU_HPP_
#define _MENU_HPP_

#include <string>
#include "controlstate.hpp"

class Menu : public ControlState
{
	ControlState* newState;
public:
	//void draw();
	void start();
	Menu(ControlState* parent);
};

#endif