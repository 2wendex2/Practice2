#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include <string>

class Text
{
public:
	static void draw(int x, int y, int w, int h, std::string s, int sze, float r, float g, float b);
};

#endif