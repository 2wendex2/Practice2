#ifndef _CONTROLSTATE_HPP_
#define _CONTROLSTATE_HPP_

class ControlState
{
protected:
	ControlState* parent;
	

public:
	ControlState(ControlState* parent) : parent(parent) {}
	virtual void draw() {};
	virtual void update() {};
	virtual void mousePress(int x, int y) {};
	virtual void mouseRelease(int x, int y) {};
	virtual void mouseMove(int x, int y) {};
	virtual void charGet(unsigned int c) {};
	virtual void keyGet(int key) {};
	virtual void start() {};
	virtual ~ControlState() {};
	void quit();
};

#endif // !_CONTROLSTATE_HPP_