#include "player.hpp"

void Player::initHand(Deck deck) {
	for (int i = 0; i < 10; i++) {
		Player::hand.push_back(deck.cards[i]);
	}
}









