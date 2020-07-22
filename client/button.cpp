#include "button.hpp"
#include "graphics.hpp"

bool Button::isInside(int _x, int _y)
{
	return _x >= x && _x < x + w && _y >= y && _y < y + h;
}

void Button::move(int _x, int _y)
{
	if (isInside(_x, _y))
		moved = true;
	else
		moved = false;
}

void Button::press(int _x, int _y)
{
	if (isInside(_x, _y))
		pressed = true;
}

void Button::release(int _x, int _y)
{
	if (isInside(_x, _y) && pressed)
		pressing();
	pressed = false;
	moved = false;
}

Button::Button(int x, int y, int w, int h) : x(x), y(y), w(w), h(h), moved(false), pressed(false) {}