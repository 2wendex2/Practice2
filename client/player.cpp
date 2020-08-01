#include "player.hpp"

void Player::initHand() {
	for (int i = 0; i < 10; i++) {
		Player::hand.push_back(this->deck.cards[i]);
	}
}

int Player::getScore() {
	this->score = 10 - this->hand.size();
	return this->score;
}









