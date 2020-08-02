#include "control.hpp"
#include "graphics.hpp"
#include "menu.hpp"
#include <iostream>
#include "settings.hpp"
#include "coretest.hpp"

int main(int argc, char** argv) {
	if (argc == 2 && std::string(argv[1]) == "test")
	{
		testCore();
		return 0;
	}
	settings.load();
	Control::init(800, 600, u8"Игра Умара");
	std::string s = "";
	Menu t(0);
	Control::changeState(&t);
	Control::mainCycle();
	Control::destroy();
	return 0;
}