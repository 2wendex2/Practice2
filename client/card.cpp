#include "card.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
 
Card deck[16];

void Card::createFullDeck() {
	deck[0].name = "candle";
	deck[0].element = "fire";
	deck[0].power = 1;

	deck[1].name = "light";
	deck[1].element = "fire";
	deck[1].power = 2;

	deck[2].name = "bonfire";
	deck[2].element = "fire";
	deck[2].power = 3;

	deck[3].name = "volcano";
	deck[3].element = "fire";
	deck[3].power = 4;


	deck[4].name = "sand";
	deck[4].element = "land";
	deck[4].power = 1;

	deck[5].name = "stone";
	deck[5].element = "land";
	deck[5].power = 2;

	deck[6].name = "mount";
	deck[6].element = "land";
	deck[6].power = 3;

	deck[7].name = "quake";
	deck[7].element = "land";
	deck[7].power = 4;


	deck[8].name = "blob";
	deck[8].element = "water";
	deck[8].power = 1;

	deck[9].name = "puddle";
	deck[9].element = "water";
	deck[9].power = 2;

	deck[10].name = "shower";
	deck[10].element = "water";
	deck[10].power = 3;

	deck[11].name = "tsunami";
	deck[11].element = "water";
	deck[11].power = 4;

	deck[12].name = "wind";
	deck[12].element = "air";
	deck[12].power = 1;

	deck[13].name = "breeze";
	deck[13].element = "air";
	deck[13].power = 2;

	deck[14].name = "tempest";
	deck[14].element = "air";
	deck[14].power = 3;

	deck[15].name = "hurricane";
	deck[15].element = "air";
	deck[15].power = 4;
}

std::vector<Card>& Card::createMyDeck(Card* deck) {
	int size = 16;
	srand(time(0));
	for (int i = 0; i < size; ++i)
		std::swap(deck[i], deck[std::rand() % size]);

	std::vector<Card> myDeck;
	for (int i = 0; i < 10; i++) {
		myDeck.push_back(deck[i]);
	}

	return myDeck;
}

void Card::createTwoDeks() {
	createFullDeck();
	std::vector<Card> playerOneDeck = createMyDeck(deck);
	std::vector<Card> playerTwoDeck = createMyDeck(deck);
}



