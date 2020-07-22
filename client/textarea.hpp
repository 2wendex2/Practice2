#ifndef _TEXTAREA_HPP_
#define _TEXTAREA_HPP_

#include <string>
#include "controlstate.hpp"

class TextArea : public ControlState
{
	std::string& enteredString;
	const std::string header;
	int maxSymbols;
public:
	void draw();
	void charGet(unsigned int c);
	void keyGet(int key);
	void start();
	TextArea(ControlState* parent, std::string &s, const std::string& header, unsigned int maxSymbols);
};

#endif