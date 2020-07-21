#ifndef _CONTROL_HPP_
#define _CONTROL_HPP_

#include "controlstate.hpp"

class Control
{
public:
	static void init(int width, int height, const char* windowName);
	static void mainCycle();
	static void destroy();
	static void changeState(ControlState* controlState);
};

#endif