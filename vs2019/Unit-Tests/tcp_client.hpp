#ifndef _TCP_CLIENT_HPP_
#define _TCP_CLIENT_HPP_

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class tcp_client {
private:
	SOCKET ConnectSocket = INVALID_SOCKET;
	bool is_valid = false;
public:
	tcp_client() {}
	void create(const char* adress, const char* port);
	int send_message(const char* sendbuf);
	std::string recieve_message();
	bool valid();
	int shut();
	void recreate(const char* adress, const char* port);
};

#endif