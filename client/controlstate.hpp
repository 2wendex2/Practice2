#ifndef _CONTROLSTATE_HPP_
#define _CONTROLSTATE_HPP_

class ControlState
{
protected:
	ControlState* parent;
	ControlState(ControlState *parent) : parent(parent) {}

public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void mousePress(int x, int y) = 0;
	virtual void mouseRelease(int x, int y) = 0;
	//virtual void charGet(char c) = 0;
	void quit();
};

#endif // !_CONTROLSTATE_HPP_