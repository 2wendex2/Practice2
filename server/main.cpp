#include <iostream>
#include <asio.hpp>
#include <vector>

using asio::ip::tcp;

int main() {
	try {
		std::cout << "ayy\n";
		asio::io_context io_context;
		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));
		tcp::socket socket(io_context);
		acceptor.accept(socket);
		int time = 0;

		for (;;) {
			time++;

			std::vector<char> buf(128);
			asio::error_code error;

			size_t len = socket.read_some(asio::buffer(buf), error);

			if (error != asio::error::eof && error) {
				std::cout << error;
				throw asio::system_error(error);
			}
			//std::cout.write(buf.data(), len);

			if (error == asio::error::eof) {
				std::cout << "socket eof\n";
			}

			std::string str(buf.data());
			if (str != "") {
				std::cout << time << std::endl;
			}

			std::cout << str;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "\n-end-\n";
	return 0;
}