#include "control.hpp"
#include <glfw3.h>
#include <iostream>
#include <exception>
#include <string>
#include "spritepool.hpp"

using namespace std;

static GLFWwindow* window;
static int screenWidth, screenHeight;
static ControlState *controlState;

static void errorCallback(int error, const char* description)
{
	string s = "GLFW error callback: ";
	s += description;
	throw std::runtime_error(s);
}

static void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SpritePool::a.draw(0, 0);
	glfwSwapBuffers(window);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
}

//void sizeCallback(GLFWwindow* window, int width, int height)
//{
	//resize(width, height);
//}

void Control::init(int width, int height, const char* windowName, ControlState *controlState)
{
	::controlState = controlState;
	screenWidth = width;
	screenHeight = height;

	glfwSetErrorCallback(errorCallback);
	if (glfwInit() == GLFW_FALSE)
		throw std::runtime_error("Failed to init GLFW");

	window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to init GLFW");
	}

	glfwMakeContextCurrent(window);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	//glfwSetMouseButtonCallback(controlImpl.window, mouseCallback);
	glfwSwapInterval(1);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 800, 600, 0, -1, 1);
	SpritePool::loadAll();

	//glfwSetWindowSizeCallback(window, sizeCallback);
}

void Control::mainCycle()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();


		draw();
		
	}
}

void Control::destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}