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

static void charCallback(GLFWwindow* window, unsigned int codepoint)
{
	controlState->charGet(codepoint);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		controlState->keyGet(key);
}

static void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	controlState->draw();
	glfwSwapBuffers(window);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		double dx, dy;
		glfwGetCursorPos(window, &dx, &dy);
		if (action == GLFW_PRESS)
			controlState->mousePress((int)dx, (int)dy);
		else
			controlState->mouseRelease((int)dx, (int)dy);
	}
}

//void sizeCallback(GLFWwindow* window, int width, int height)
//{
	//resize(width, height);
//}

void Control::init(int width, int height, const char* windowName)
{
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
	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetCharCallback(window, charCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSwapInterval(1);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 800, 600, 0, -1, 1);
	SpritePool::loadAll();

	//glfwSetWindowSizeCallback(window, sizeCallback);
}

void Control::changeState(ControlState* newControlState)
{
	if (newControlState)
	{
		controlState = newControlState;
		controlState->start();
	}
	else
		glfwSetWindowShouldClose(window, true);
}

void Control::mainCycle()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		controlState->update();
		draw();
	}
}

void Control::destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}