#include <glfw3.h>

#include <cassert>
#include "../client/settings.hpp"
#include "../client/control.hpp"
#include "../client/graphics.hpp"
#include "../client/controlstate.hpp"
#include "../client/gamewaiting.hpp"
#include "../client/textarea.hpp"
#include "../client/menubuttons.hpp"
#include "../client/menu.hpp"
#include "../client/game.hpp"
#include "../servercmd.hpp"

#include <iostream>

#include "coretest.hpp"

//Тесты для ядра клиента

static void testSettings()
{
	Settings ts;
	ts.host = "127.0.0.1:13";
	ts.save();
	ts.host = "DT";
	ts.load();
	assert(std::string("127.0.0.1:13") == ts.host);
	std::cout << "settings completed" << std::endl;
}

static void testControl()
{
	Control::init(800, 600, u8"Тест");
	ControlState st = ControlState(0);
	Control::changeState(&st);
	assert(&st == Control::getState());
	std::cout << "control completed" << std::endl;
}

static void testGraphics()
{
	class TestState : public ControlState
	{
	public:
		int c = 60;
		TestState() : ControlState(0) {}

		void draw() {
			Graphics::changeBackgroundColor(1.f, 1.f, 1.f);
			Graphics::changeColor(1.f, 1.f, 1.f);
		}

		void update()
		{
			c--;
			if (c < 0)
				Control::changeState(0);
		}
	} st;

	Control::changeState(&st);
	Control::mainCycle();
	assert(st.c < 0);
	std::cout << "graphics completed" << std::endl;
}

static void testServerCmd()
{
	Servercmd cmd(" fg t h  ");
	assert(cmd.size() == 3);
	assert(cmd[0] == "fg");
	assert(cmd[1] == "t");
	assert(cmd[2] == "h");
	assert(cmd[3] == "");
	assert(cmd[4] == "");
	std::cout << "servercmd completed" << std::endl;
}

static void testGameWaiting()
{
	ControlState st = ControlState(0);
	GameWaiting gw(&st, "");
	Control::changeState(&gw);
	gw.keyGet(GLFW_KEY_ESCAPE);
	assert(Control::getState() == &st);
	std::cout << "gamewaiting completed" << std::endl;
}

static void testTextArea()
{
	std::string s = "aab";
	TextArea ta(0, s, "", 5);
	ta.charGet('q');
	ta.charGet('w');
	ta.charGet('e');
	assert(s == "aabqw");
	std::cout << "textarea completed" << std::endl;
}

static void testMenuButtons()
{
	GameButton gb(0, 0, 1, 1);
	gb.getStr() = "azaza";
	assert(gb.getStr() == "azaza");
	std::cout << "menubuttons completed" << std::endl;
}

void testMenu()
{
	Menu menu(0);
	settings.host = "";
	menu.changeServer();
	((TextArea*)Control::getState())->charGet('R');
	std::cout << "Trying to connect to non existing server ";
	((TextArea*)Control::getState())->keyGet(GLFW_KEY_ENTER);
	assert(settings.host == "R");
	std::cout << "menu completed" << std::endl;
}

void testGame()
{
	ControlState st(0);
	Game game(&st);
	game.keyGet(GLFW_KEY_ESCAPE);
	assert(Control::getState() == &st);
	std::cout << "game completed" << std::endl;
}

void testCore()
{
	testSettings();
	testControl();
	testGraphics();
	testServerCmd();
	testGameWaiting();
	testTextArea();
	testMenu();
	testGame();
	std::cout << "all tests completed\nSUCCESS" << std::endl;
}