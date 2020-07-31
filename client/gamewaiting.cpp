#include "gamewaiting.hpp"
#include "spritepool.hpp"
#include <iostream>
#include "text.hpp"

void GameWaiting::draw()
{
	Text::draw(400, 300, 800, 600, "Waiting for player", 64, 0.f, 0.7f, 1.f);
}

void GameWaiting::update() {}

GameWaiting::GameWaiting(ControlState* parent) : ControlState(parent) {}
