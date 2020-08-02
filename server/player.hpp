#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <vector>
#include"card.hpp"


class Player {

public:
	 std::vector<int> hand;
	 Player() {
		 this->initHand();
	 }

	int getPower(int id);
	int getElement(int id);

private:
	void initHand();

};

#endif