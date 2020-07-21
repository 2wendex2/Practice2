#include <iostream>
#include <asio.hpp>
#include <vector>
#include "dialog.hpp"

using asio::ip::tcp;

int main() {
	try {
		asio::io_context io_context;
		asio::steady_timer t(io_context, asio::chrono::seconds(3));
		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints =
			resolver.resolve("127.0.0.1", "daytime");
		tcp::socket socket(io_context);
		asio::connect(socket, endpoints);
		int iter = 0;
		for (;;) {
			if (iter == 101) {
				socket.close();
				break;
			}
			iter++;

			if (iter % 25 == 0) {
				std::string message = "ALO ";
				send_message(&socket, message);
				t.wait();
			}	
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Finished\n";
	return 0;
}