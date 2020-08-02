#include "player.hpp"
#include <algorithm>

void Player::initHand() {
	int array[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
					 10, 11, 12, 13, 14, 15 };
	std::random_shuffle(array, array + 16);
	for (int i = 0; i < 10; i++) {	
		hand.push_back(array[i]);
	}
}

int Player::getPower(int id) {
	return Card::powerArray[id];
}

int Player::getElement(int id) {
	return Card::elementArray[id];
}










