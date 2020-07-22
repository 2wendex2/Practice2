#include "graphics.hpp"
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

void Graphics::changeBackgroundColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1.f);
}

