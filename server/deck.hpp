#ifndef _DECK_HPP_
#define _DECK_HPP_

#include "card.hpp"
#include <vector>

class Deck {
public:
	std::vector<Card> cards;

public:
	void createDeck(); 
	void myShuffle();

public:	    
	Deck() {
		createDeck();
	}
};

#endif