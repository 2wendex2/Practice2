#include "pch.h"
#include <gtest/gtest.h>
#include "tcp_client.hpp"

tcp_client* client1;
tcp_client* client2;
tcp_client* client3;

std::string get_msg(tcp_client* client) {
	std::string str;
	for (int i = 0; i < 150000; i++) {
		str = client->recieve_message();
		if (str != "") {
			//std::cout << i << std::endl;
			break;
		}
	}
	return str;
}

TEST(ServerInteractionsWithSingleClient, CreateLobby) {
  client1 = new tcp_client();
  client1->create("127.0.0.1", "13");
  
  std::string str = "";
  client1->send_message("newgame mygame\n");
  str = get_msg(client1);
  EXPECT_EQ(str, "list mygame\n");
}


TEST(ServerInteractionsWithSingleClient, DeleteLobby) {
	std::string str = "";
	client1->send_message("delete mygame\n");
	str = get_msg(client1);
	EXPECT_EQ(str, "delete mygame\n");
}


TEST(ServerInteractionsWithMultipleClients, UpdateLobbyList) {
	client2 = new tcp_client();
	client2->create("127.0.0.1", "13");
	client3 = new tcp_client();
	client3->create("127.0.0.1", "13");

	std::string str1 = "";
	std::string str2 = "";
	std::string str3 = "";

	client2->send_message("newgame mygame\n");
	str1 = get_msg(client1);
	str3 = get_msg(client3);
	EXPECT_EQ(str1, "list mygame\n");
	EXPECT_EQ(str3, "list mygame\n");

	str1 = "";
	str2 = "";
	str3 = "";

	client2->send_message("delete mygame\n");
	str1 = get_msg(client1);
	str3 = get_msg(client3);
	EXPECT_EQ(str1, "delete mygame\n");
	EXPECT_EQ(str3, "delete mygame\n");

	get_msg(client2);
}


TEST(ServerInteractionsWithMultipleClients, ConnectingToLobbyAndStartingGame) {
	std::string str1 = "";
	std::string str2 = "";
	std::string str3 = "";

	client1->send_message("newgame mygame\n");
	str1 = get_msg(client1);
	str2 = get_msg(client2);
	str3 = get_msg(client3);
	EXPECT_EQ(str1, "list mygame\n");
	EXPECT_EQ(str2, "list mygame\n");
	EXPECT_EQ(str3, "list mygame\n");

	str1 = "";
	str2 = "";
	str3 = "";

	client2->send_message("game mygame\n");
	str1 = get_msg(client1);
	str2 = get_msg(client2);
	str3 = get_msg(client3);
	EXPECT_EQ(str1, "start\n");
	EXPECT_EQ(str2, "start\n");
	EXPECT_EQ(str3, "delete mygame\n");
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}