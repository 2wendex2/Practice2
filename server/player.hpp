#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <vector>
#include"card.hpp"


class Player {

public:
	 std::vector<int> hand;
	 bool trueCard[10];
	 int score = 0;
	 Player() {
		 this->initHand();
		 for (int i = 0; i < 10; i++) {
			 this->trueCard[i] = true;
		 }
	 }

	int getPower(int id);
	Card::Element getElement(int id);

private:
	void initHand();

};

#endif