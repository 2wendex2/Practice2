#include <iostream>
#include <asio.hpp>

using namespace std;
using asio::ip::tcp;

int main()
{
	cout << "aee";
	asio::io_context io_context;
	tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8014));
	tcp::socket socket(io_context);
	acceptor.accept(socket);
	cout << "sasalovo";
	return 0;
}