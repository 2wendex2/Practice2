#include <iostream>
#include <vector>

class Lobby {
public:
	int player1_id = NULL;
	int player2_id = NULL;
	std::string lobby_name;
	Lobby(int creator_id, std::string name);
};