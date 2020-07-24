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
	tcp_client(const char* adress, const char* port) {
		WSADATA wsaData;
		int iResult;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed: %d\n", iResult);
			return;
		}

		struct addrinfo* result = NULL, * ptr = NULL, hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		iResult = getaddrinfo("127.0.0.1", "13", &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return;
		}

		ptr = result;

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return;
		}

		unsigned long ul = 1;
		int nRet;
		nRet = ioctlsocket(ConnectSocket, FIONBIO, (unsigned long*)&ul);

		if (nRet == SOCKET_ERROR) {
			printf("Failed to put the socket into non-blocking mode\n");
			WSACleanup();
			return;
		}

		// Connect to server.
		for (int i = 0; ; i++) {
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (i == 100) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				break;
			} else if (iResult == SOCKET_ERROR) {
				long last_err = WSAGetLastError();
				if (last_err == 10035) continue;
				if (last_err == 10037) continue;
				if (last_err == 10056) break;
				printf("Error at connect(): %ld\n", last_err);
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				break;
			} else {
				printf("KAK TI SUDA POPAL?\n");
				break;
			}
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return;
		}

		is_valid = true;
	}
	
	int send_message(const char* sendbuf) {
		int iResult;
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		printf("Bytes Sent: %ld\n", iResult);
		return 0;
	}

	std::string recieve_message() {
		int recvbuflen = 128;
		int iResult;
		char recvbuf[128];
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult >= 0) {
			printf("Bytes received: %d\n", iResult);
			recvbuf[iResult] = 0;
			std::string str(recvbuf);
			std::cout << str << std::endl;
			return str;
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			return "";
		}
	}

	bool valid() {
		return is_valid;
	}

	int shut() {
		int iResult;
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		closesocket(ConnectSocket);
		WSACleanup();
	}
};