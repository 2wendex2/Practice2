#include "text.hpp"
#include "spritepool.hpp"
#include <GLFW/glfw3.h>

void Text::draw(int x, int y, int w, int h, std::string s, int sze, float r, float g, float b)
{
	int n = s.length();
	if (n == 0)
		return;

	x++; y++;
	int cap = 8;
	
	int sx = w / sze; //Максимальное количество символов в строке
	int sy = h / sze; //~ в столбце
	int ny = (n + sx - 1) / sx; //количество символов в столбце
	int nnx = n - (ny - 1) * sx; //количество символов в последней строке
	int nx = (ny == 1) ? nnx : sx; //количество символов в строке
	int xf = x - sze * (nnx / 2);

	if (sx % 2)
		x -= sze / 2;

	if (nnx % 2)
		xf -= sze / 2;

	if (ny % 2)
		y -= sze / 2;

	
	x -= sze * (nx / 2);
	y -= sze * (ny / 2);

	glColor3f(r, g, b);
	int c = 0;
	for (int i = 0; i < ny - 1; i++)
		for (int j = 0; j < sx; j++)
		{
			float tx = 1.f / 16 * ((unsigned char)s[c] % 16);
			float ty = 1.f / 16 * ((unsigned char)s[c] / 16);
			SpritePool::font.drawPart(x + sze * j, y + sze * i, tx, ty, tx + 1.f / 16, ty + 1.f / 16, sze, sze);
			c++;
		}

	for (int j = 0; j < nnx; j++)
	{
		float tx = 1.f / 16 * ((unsigned char)s[c] % 16);
		float ty = 1.f / 16 * ((unsigned char)s[c] / 16);
		SpritePool::font.drawPart(xf + sze * j, y + sze * (ny - 1), tx, ty, tx + 1.f / 16, ty + 1.f / 16, sze, sze);
		c++;
	}
	glColor3f(1.f, 1.f, 1.f);
}