#include "control.hpp"
#include "graphics.hpp"

int main() {
	Control::init(800, 600, u8"Игра Умара", 0);
	Graphics::changeBackgroundColor(0.f, 1.f, 0.f);
	Control::mainCycle();
	Control::destroy();
	return 0;
}