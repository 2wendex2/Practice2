#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <vector>



class Player {

public:
	 std::vector<int> hand;
	 Player() {
		 this->initHand();
	 }

private:
	void initHand();

};

#endif