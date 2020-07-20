#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int send_message(tcp::socket *socket, std::string message){
	asio::error_code ignored_error;
	asio::write(*socket, asio::buffer(message), ignored_error);

	if (ignored_error){
		std::cout << ignored_error << std::endl;
	}
	return 0;
}