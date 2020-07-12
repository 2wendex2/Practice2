#include "game.hpp"
#include "spritepool.hpp"
#include <iostream>

void Game::draw()
{
	SpritePool::a.draw(0, 0);
}

void Game::update() {}

Game::Game(ControlState* parent) : ControlState(parent) {}

void Game::mousePress(int x, int y) { std::cout << x << ' ' << y << std::endl; }
void Game::mouseRelease(int x, int y) { std::cout << x << ' ' << y << ' ' << "LUPA" << std::endl; }