#include "control.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "player.hpp"
#include <ctime>
#include <iostream>

int main() {
	Game game(0);
	Control::init(800, 600, u8"Игра Умара", &game);
	Graphics::changeBackgroundColor(0.f, 1.f, 0.f);
	Control::mainCycle();
	Control::destroy();
	
	
	return 0;
}