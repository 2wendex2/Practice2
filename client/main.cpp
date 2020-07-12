#include "control.hpp"
#include "graphics.hpp"
#include "game.hpp"

int main() {
	Game game(0);
	Control::init(800, 600, u8"���� �����", &game);
	Graphics::changeBackgroundColor(0.f, 1.f, 0.f);
	Control::mainCycle();
	Control::destroy();
	return 0;
}