#include "game.hpp"
#include "spritepool.hpp"
#include <iostream>
#include "text.hpp"

void Game::draw()
{
	Text::draw(400, 300, 800, 600, "GAME", 64, 0.f, 0.7f, 1.f);
}

void Game::update() {}

Game::Game(ControlState* parent) : ControlState(parent) {}

void Game::mousePress(int x, int y) { std::cout << x << ' ' << y << std::endl; }
void Game::mouseRelease(int x, int y) { std::cout << x << ' ' << y << ' ' << "LUPA" << std::endl; }
void Game::charGet(char c) {}
