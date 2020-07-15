#ifndef _CARD_HPP_
#define _CARD_HPP_
#include <vector>

class Card {

	const char* name;
	const char* element;
	int power;

public:
	static void createFullDeck();
	static std::vector<Card>& createMyDeck(Card* deck);
	static void createTwoDeks();
};

#endif