#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <vector>
#include "deck.hpp"


class Player {

public:
	 std::vector<Card> hand;
	 int score;
	 Deck deck;
	 Player() {
		 this->initHand();
	 }

private:
	void initHand();

public:
	int getScore();
};

#endif