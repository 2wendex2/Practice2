#ifndef _DECK_HPP_
#define _DECK_HPP_

#include "card.hpp"
#include <vector>

class Deck {
public:
	std::vector<Card> cards;

private:
	void createDeck(); 
	void shuffle();

public:	    
	Deck() {
		createDeck();
		shuffle();
		shuffle();
		shuffle();
		shuffle();
		shuffle();
	}
};

#endif