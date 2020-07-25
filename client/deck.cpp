#include "deck.hpp"
#include <iostream>     
#include <algorithm>    
#include <random>     
#include <chrono>  

void Deck::createDeck() {
	this->cards.push_back({ "candle", "fire", 1, 1 }); 
	this->cards.push_back({ "light", "fire", 2, 2 });
	this->cards.push_back({ "bonfire", "fire", 3, 3 });
	this->cards.push_back({ "volcano", "fire", 4, 4 });
	this->cards.push_back({ "sand", "land", 1, 5 });
	this->cards.push_back({ "stone", "land", 2, 6 });
	this->cards.push_back({ "mount", "land", 3, 7 });
	this->cards.push_back({ "quake", "land", 4, 8 });
	this->cards.push_back({ "blob", "water", 1, 9 });
	this->cards.push_back({ "puddle", "water", 2, 10 });
	this->cards.push_back({ "shower", "water", 3, 11 });
	this->cards.push_back({ "tsunami", "water", 4, 12 });
	this->cards.push_back({ "cloud", "air", 1, 13 });
	this->cards.push_back({ "wind", "air", 2, 14 });
	this->cards.push_back({ "tempest", "air", 3, 15 });
	this->cards.push_back({ "hurricane", "air", 4, 16 });
}

void Deck::shuffle() {
	srand(time(0));
	for (int i = 0; i < this->cards.size(); ++i)
		std::swap(this->cards[i], this->cards[rand() % this->cards.size()]);
}

