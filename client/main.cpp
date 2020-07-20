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
			//std::cout << "g";
			//asio::streambuf read_buffer;
			//asio::error_code error;

			//if (error == asio::error::eof)
				//break; // Connection closed cleanly by peer.
			//else if (error)
				//throw asio::system_error(error); // Some other error.

			if (iter % 25 == 0) {
				//std::string message = "ALO\n";
				std::string message = "XUY ";
				send_message(&socket, message);
				//asio::error_code ignored_error;
				//asio::write(socket, asio::buffer(message), ignored_error);
				t.wait();
			}	
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Ger Nick";
	return 0;
}