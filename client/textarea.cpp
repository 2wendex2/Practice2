#include "textarea.hpp"
#include "spritepool.hpp"
#include "graphics.hpp"
#include <iostream>
#include "text.hpp"
#include <glfw3.h>
#include "control.hpp"

//24*17 максимум

TextArea::TextArea(ControlState* parent, std::string& s, const std::string& header, unsigned int maxSymbols) : ControlState(parent),
enteredString(s), header(header), maxSymbols(maxSymbols)
{
	Graphics::changeBackgroundColor(0.f, 0.f, 0.f);
}

void TextArea::start()
{
	Graphics::changeBackgroundColor(0.f, 0.f, 0.f);
}

void TextArea::draw()
{
	Text::draw(400, 32 - 8, 800, 64 - 16, header, 32, 0.f, 0.7f, 1.f);
	Text::draw(400, 316, 800 - 16, 600, enteredString, 32, 1.f, 1.f, 1.f);
}

void TextArea::charGet(unsigned int c)
{
	if (c < 128 && enteredString.length() < maxSymbols)
		enteredString += (char)c;
}

void TextArea::keyGet(int key)
{
	switch (key)
	{
	case GLFW_KEY_BACKSPACE:
		if (enteredString.length() > 0)
			enteredString.pop_back();
		break;
	case GLFW_KEY_ESCAPE:
		enteredString.clear();
	case GLFW_KEY_ENTER:
		Control::changeState(parent);
		break;
	}
}
