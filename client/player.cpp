#include "player.hpp"

void Player::initHand(Deck deck) {
	for (int i = 0; i < 10; i++) {
		Player::hand.push_back(deck.cards[i]);
	}
}

/*void Player::makeCor(int centreX, int centreY, int dist) {
	for (int i = 0; i < Player::hand.size(); i++) {
		int x1 = centreX - Player::hand[i].r;
		int x2 = centreX + Player::hand[i].r;
		int y1 = centreY - Player::hand[i].R;
		int y2 = centreY + Player::hand[i].R;
		Player::hand[i].pushCord(x1, y1, x2, y2);
		centreX += 2 * Player::hand[i].r + dist;
	}
} */
 







