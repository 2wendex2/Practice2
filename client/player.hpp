#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <vector>
#include "deck.hpp"


class Player {

public:
	 std::vector<Card> hand;

	 Player(Deck deck) {
		 this->initHand(deck);
	 }

private:
	void initHand(Deck deck);
public:
	void makeCor(int centreX, int centreY, int dist);
};

#endif