#include "control.hpp"
#include "graphics.hpp"
#include "menu.hpp"
#include <iostream>
//<<<<<<< HEAD
#include "settings.hpp"

int main() {
	settings.load();
	Control::init(800, 600, u8"Игра Умара");
	std::string s = "";
	Menu t(0);
	Control::changeState(&t);
	Control::mainCycle();
	Control::destroy();
	std::cout << s;
//=======
/*#include "tcp_client.hpp"


int main() {
	tcp_client* client = new tcp_client("127.0.0.1", "13");
	if (client->valid()) {
		for (int i = 1; i < 100; i++) {
			if (i == 55) {
				std::cout << i << "=>    ";
				const char* message = "mint ";
				client->send_message(message);
				std::string str = client->recieve_message();
			} else if (i % 5 == 0){
				std::cout << i << "=>    ";
				const char* message = "ALO ";
				client->send_message(message);
				std::string str = client->recieve_message();
			}
		}

		std::cout << "Finished\n";
		client->shut();
	} else {
		std::cout << "Invalid client\n";
	}*/
//>>>>>>> origin/glebdev
	return 0;
}