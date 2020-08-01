#include "deck.hpp"
#include <iostream>     
#include <algorithm>    
#include <cstdlib>     


void Deck::createDeck() {
	this->cards.push_back({ "candle", "fire", 1, 0 }); 
	this->cards.push_back({ "light", "fire", 2, 1 });
	this->cards.push_back({ "bonfire", "fire", 3, 2 });
	this->cards.push_back({ "volcano", "fire", 4, 3 });
	this->cards.push_back({ "sand", "land", 1, 4 });
	this->cards.push_back({ "stone", "land", 2, 5 });
	this->cards.push_back({ "mount", "land", 3, 6 });
	this->cards.push_back({ "quake", "land", 4, 7 });
	this->cards.push_back({ "blob", "water", 1, 8 });
	this->cards.push_back({ "puddle", "water", 2, 9 });
	this->cards.push_back({ "shower", "water", 3, 10 });
	this->cards.push_back({ "tsunami", "water", 4, 11 });
	this->cards.push_back({ "cloud", "air", 1, 12 });
	this->cards.push_back({ "wind", "air", 2, 13 });
	this->cards.push_back({ "tempest", "air", 3, 14 });
	this->cards.push_back({ "hurricane", "air", 4, 15 });
}

void Deck::shuffle() {
	for (int i = 0; i < this->cards.size(); i++)
		std::swap(this->cards[i], this->cards[rand() % this->cards.size()]);
}


