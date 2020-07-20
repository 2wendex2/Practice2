#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int send(tcp::socket* socket, std::string message);