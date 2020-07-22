#include "spritepool.hpp"
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <string>

static const std::string IMAGE_PATH = "DATA/img/";

void Sprite::load(const char* name)
{
	unsigned char* img = SOIL_load_image((IMAGE_PATH + name).c_str(), &w, &h, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::draw(int x, int y)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex2f(x, y);
	glTexCoord2f(1, 0);		glVertex2f(x+w, y);
	glTexCoord2f(1, 1);		glVertex2f(x+w, y+h);
	glTexCoord2f(0, 1);		glVertex2f(x, y+h);
	glEnd();
}

void Sprite::drawPart(int x, int y, float tl, float tt, float tr, float tb,float w, float h)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(tl, tt);		glVertex2f(x, y);
	glTexCoord2f(tr, tt);		glVertex2f(x + w, y);
	glTexCoord2f(tr, tb);		glVertex2f(x + w, y + h);
	glTexCoord2f(tl, tb);		glVertex2f(x, y + h);
	glEnd();
}

Sprite SpritePool::font;
Sprite SpritePool::cerber;

void SpritePool::loadAll()
{
	font.load("font.png");
	cerber.load("cerber.png");
}