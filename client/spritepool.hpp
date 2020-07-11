#include "graphics.hpp"

class Sprite
{
	int w, h;
	unsigned int texture;

	void load(const char* name);

public:
	void draw(int x, int y);
	void drawPart(int x, int y, float tl, float tt, float tr, float tb);
	friend class SpritePool;
};


class SpritePool
{
	static Sprite loadSprite();

public:
	static Sprite a;

	static void loadAll();
};