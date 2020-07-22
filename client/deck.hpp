#ifndef _DECK_HPP_
#define _DECK_HPP_

#include "card.hpp"
#include <vector>

class Deck {
public:
	std::vector<Card> cards;

private:
	void createDeck();

public: 
	void shuffle();


	Deck() {
		shuffle();
	}
};

#endif