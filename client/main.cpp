#include "control.hpp"
#include "graphics.hpp"
#include "textarea.hpp"
#include <iostream>
#include "settings.hpp"

int main() {
	settings.load();
	Control::init(800, 600, u8"Игра Умара");
	std::string s = "";
	TextArea t(0, s, "PINGAS", 24*17);
	Control::changeState(&t);
	Control::mainCycle();
	Control::destroy();
	std::cout << s;
	return 0;
}