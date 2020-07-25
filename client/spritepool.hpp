#ifndef _SPRITEPOOL_HPP_
#define _SPRITEPOOL_HPP_

#include "graphics.hpp"

class Sprite
{
	int w, h;
	unsigned int texture;

	void load(const char* name);

public:
	void draw(int x, int y);
	void drawPart(int x, int y, float tl, float tt, float tr, float tb, float w, float h);
	friend class SpritePool;
};


class SpritePool
{
public:
	static Sprite font;
	static Sprite cerber;
	static Sprite cardsTexture[];

	static void loadAll();
};

#endif