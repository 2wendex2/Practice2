#include "control.hpp"
#include "graphics.hpp"
#include "menu.hpp"
#include <iostream>
#include "settings.hpp"

int main() {
	settings.load();
	Control::init(800, 600, u8"Игра Умара");
	std::string s = "";
	Menu t(0);
	Control::changeState(&t);
	Control::mainCycle();
	Control::destroy();
	std::cout << s;
	return 0;
}