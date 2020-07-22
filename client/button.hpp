#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include "buttonabstract.hpp"
#include "spritepool.hpp"

class Button : public ButtonAbstract
{
protected:
	int x, y, w, h;
	bool moved, pressed;
	
	bool isInside(int x, int y);
public:
	void move(int x, int y);
	void press(int x, int y);
	void release(int x, int y);
	virtual void draw() = 0;
	virtual void pressing() = 0;
	Button(int x, int y, int w, int h);
};

#endif // ! _BUTTON_HPP_