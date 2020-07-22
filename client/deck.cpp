#include "deck.hpp"
#include <iostream>     
#include <algorithm>    
#include <random>     
#include <chrono>  

void Deck::createDeck() {
	Deck::cards.push_back({ "candle", "fire", 1, 1 }); 
	Deck::cards.push_back({ "light", "fire", 2, 2 });
	Deck::cards.push_back({ "bonfire", "fire", 3, 3 });
	Deck::cards.push_back({ "volcano", "fire", 4, 4 });
	Deck::cards.push_back({ "sand", "land", 1, 5 });
	Deck::cards.push_back({ "stone", "land", 2, 6 });
	Deck::cards.push_back({ "mount", "land", 3, 7 });
	Deck::cards.push_back({ "quake", "land", 4, 8 });
	Deck::cards.push_back({ "blob", "water", 1, 9 });
	Deck::cards.push_back({ "puddle", "water", 2, 10 });
	Deck::cards.push_back({ "shower", "water", 3, 11 });
	Deck::cards.push_back({ "tsunami", "water", 4, 12 });
	Deck::cards.push_back({ "wind", "air", 1, 13 });
	Deck::cards.push_back({ "breeze", "air", 2, 14 });
	Deck::cards.push_back({ "tempest", "air", 3, 15 });
	Deck::cards.push_back({ "hurricane", "air", 4, 16 });
}

void Deck::shuffle() {
	srand(time(0));
	for (int i = 0; i < Deck::cards.size(); ++i)
		std::swap(Deck::cards[i], Deck::cards[rand() % Deck::cards.size()]);
}

