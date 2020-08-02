#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

#include <iostream>
#include <vector>
#include <unordered_map>
#include "lobby.hpp"
#include "game.hpp"

static const char* MESSAGE = "Hello, World!\n";

static const int PORT = 13;

std::vector<Lobby*> pending_lobbies;
static int list_sockets[100];
static int list_sock_num = 0;
std::unordered_map<int, bufferevent*> socket_to_buffer;
std::unordered_map<int, std::string> socket_to_state;
std::unordered_map<int, Game*> socket_to_game;

void writeMesg(int fd, const std::string &msg)
{
	bufferevent_write(socket_to_buffer[(int)fd], msg.c_str(), msg.length());
}

void gameEnd(int fd)
{
	socket_to_state[fd] = "LIST";
	delete socket_to_game[fd];
	socket_to_game.erase(fd);
	list_sockets[list_sock_num] = fd;
	list_sock_num++;
}

static void listener_cb(struct evconnlistener*, evutil_socket_t, struct sockaddr*, int socklen, void*);
static void conn_writecb(struct bufferevent*, void*);
static void conn_readcb(struct bufferevent*, void*);
static void conn_eventcb(struct bufferevent*, short, void*);
static void signal_cb(evutil_socket_t, short, void*);

int main(int argc, char** argv) {
	std::cout << "START\n";

	for (int i = 0; i < 100; i++) {
		list_sockets[i] = -1;
	}

	struct event_base* base;
	struct evconnlistener* listener;
	struct event* signal_event;

	struct sockaddr_in sin = { 0 };
#ifdef _WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	base = event_base_new();
	if (!base) {
		fprintf(stderr, "Could not initialize libevent!\n");
		return 1;
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	listener = evconnlistener_new_bind(base, listener_cb, (void*)base,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&sin,
		sizeof(sin));

	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
		return 1;
	}

	signal_event = evsignal_new(base, SIGINT, signal_cb, (void*)base);

	if (!signal_event || event_add(signal_event, NULL) < 0) {
		fprintf(stderr, "Could not create/add a signal event!\n");
		return 1;
	}

	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);

	printf("done\n");
	return 0;
}

static void listener_cb(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data) {
	std::cout << "Got a connection form socket " << (int)fd << std::endl;
	struct event_base* base = (event_base*)user_data;
	struct bufferevent* bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}

	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, NULL);
	bufferevent_enable(bev, EV_READ);
	bufferevent_enable(bev, EV_WRITE);

	list_sockets[list_sock_num++] = (int)fd;
	socket_to_buffer.insert(std::make_pair((int)fd, bev));
	socket_to_state.insert(std::make_pair((int)fd, "LIST"));
}

static void conn_writecb(struct bufferevent* bev, void* user_data) {
	struct evbuffer* output = bufferevent_get_output(bev);
	//std::cout << "KAK TI SUDA POPAL\n";
	size_t len = evbuffer_get_length(output);
	if (len) {
		std::cout << "Something is wrong, len = " << len << std::endl;
	}
}

static void conn_eventcb(struct bufferevent* bev, short events, void* user_data) {
	evutil_socket_t fd = bufferevent_getfd(bev);

	int sock_desc = (int)fd;
	bool deleted = false;
	for (int i = 0; i < list_sock_num; i++) {
		if (list_sockets[i] == sock_desc) {
			for (int j = i + 1; j < list_sock_num; j++) {
				list_sockets[j - 1] = list_sockets[j];
			}
			list_sockets[--list_sock_num] = -1;
			deleted = true;
			break;
		}
	}
	socket_to_buffer.erase(sock_desc);
	socket_to_state.erase(sock_desc);

	if (events & BEV_EVENT_EOF) {
		printf("Connection from socket %d closed.\n", (int)fd);
	}
	else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection from socket %d\n", (int)fd);
	}
	
	bufferevent_free(bev);
}

static void signal_cb(evutil_socket_t sig, short events, void* user_data) {
	struct event_base* base = (event_base*)user_data;
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);
}

static void conn_readcb(struct bufferevent* bev, void* user_data) {
	std::cout << "got something to read\n";

	struct evbuffer* input = bufferevent_get_input(bev);
	size_t len = evbuffer_get_length(input);

	evutil_socket_t fd = bufferevent_getfd(bev);
	std::cout << "Socket Descriptor = " << (int)fd << ";\nMessage:";


	char* data = new char[len + 1];
	evbuffer_copyout(input, data, len);
	evbuffer_drain(input, len);
	data[len] = 0;
	
	const char* deli = "\n";
	std::string s(data);
	std::cout << s << std::endl;
	std::size_t pos = 0;
	auto au_mp = socket_to_buffer.find((int)fd);

	if (socket_to_state[(int)fd] == "GAME")
	{
		socket_to_game[(int)fd]->dispatchMsg((int)fd, s);
		return;
	}

	while (pos < s.length()) {
		std::size_t new_pos = s.find(deli, pos);
		std::string current_command = s.substr(pos, new_pos - pos);
		pos = new_pos + 1;
		std::size_t sp = 0;
		std::string name = "";
		std::string msg = "";
		auto state = socket_to_state.find((int)fd);

		switch (current_command[0]) {
		case 'l':
			//if (state->second != "LIST") break;
			printf("Listing current pending lobbies to the client\n");
			for (auto lob : pending_lobbies) {
				std::string reply = "list ";
				reply += lob->lobby_name;
				reply += '\n';
				std::cout << reply;
				bufferevent_write(bev, reply.data(), strlen(reply.data()));
			}
			break;
		case 'n':
			sp = current_command.find(' ');
			name = current_command.substr(sp + 1);
			if (name == "")
				break;

			if (state->second != "LIST") break;
			//проверить соответствие state->second

			std::cout << "creating newgame with name = " << name << ";\n";
			state->second = "LOBBY";
			pending_lobbies.push_back(new Lobby((int)fd, name));

			for (int i = 0; i < list_sock_num; i++) {
				if (list_sockets[i] == (int)fd) {
					for (int j = i + 1; j < list_sock_num; j++) {
						list_sockets[j - 1] = list_sockets[j];
					}
					list_sockets[--list_sock_num] = -1;
					break;
				}
			}

			msg = "newgame ";
			msg += name;
			msg += '\n';
			bufferevent_write(au_mp->second, msg.data(), strlen(msg.data()));

			msg = "list ";
			msg += name;
			msg += '\n';

			for (int i = 0; i < list_sock_num; i++) {
				auto mp = socket_to_buffer.find(list_sockets[i]);
				std::cout << msg << " ++ to socket = " << list_sockets[i] << "; buffer = " << mp->second << ";\n";
				bufferevent_write(mp->second, msg.data(), strlen(msg.data()));
				//bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
			}
			break;
		case 'd':
			sp = current_command.find(' ');
			name = current_command.substr(sp + 1);
			std::cout << "deleting game with name = " << name << ";\n";
			state->second = "LIST";

			for (auto el : pending_lobbies) {
				if (el->lobby_name == name) {
					std::cout << "found the right lobby\n";
					if (el->player1_id > 0) {
						list_sockets[list_sock_num++] = el->player1_id;
					}
					if (el->player2_id > 0) {
						list_sockets[list_sock_num++] = el->player2_id;
					}

					el->player1_id = pending_lobbies[pending_lobbies.size() - 1]->player1_id;
					el->player2_id = pending_lobbies[pending_lobbies.size() - 1]->player2_id;
					el->lobby_name = pending_lobbies[pending_lobbies.size() - 1]->lobby_name;
					delete pending_lobbies[pending_lobbies.size() - 1];
					pending_lobbies.pop_back();

					msg += "delete ";
					msg += name;
					msg += '\n';

					for (int i = 0; i < list_sock_num; i++) {
						auto mp = socket_to_buffer.find(list_sockets[i]);
						std::cout << msg << " ++ to socket = " << list_sockets[i] << "; buffer = " << mp->second << ";\n";
						bufferevent_write(mp->second, msg.data(), strlen(msg.data()));
						//bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
					}
					break;
				}
			}

			break;
		case 'g':
			sp = current_command.find(' ');
			name = current_command.substr(sp + 1);
			std::cout << "connecting to game with name = " << name << ";\n";

			for (auto el : pending_lobbies) {
				if (el->lobby_name == name) {
					std::string start_msg = "start\n";
					std::cout << "found the right lobby\n";
					state->second = "GAME";
					el->player2_id = (int)fd;
					socket_to_game[(int)fd] = new Game(el->player1_id, el->player2_id);

					for (int i = 0; i < list_sock_num; i++) {
						if (list_sockets[i] == (int)fd) {
							for (int j = i + 1; j < list_sock_num; j++) {
								list_sockets[j - 1] = list_sockets[j];
							}
							list_sockets[--list_sock_num] = -1;
							break;
						}
					}

					auto mp1 = socket_to_buffer.find(el->player1_id);
					auto state1 = socket_to_state.find(el->player1_id);
					//можно проверить соответствие состояния 1ого игрока "LOBBY"
					state1->second = "GAME";
					//mp2 eto bev
					bufferevent_write(mp1->second, start_msg.data(), strlen(start_msg.data()));
					bufferevent_write(bev, start_msg.data(), strlen(start_msg.data()));

					msg += "delete ";
					msg += name;
					msg += '\n';

					for (int i = 0; i < list_sock_num; i++) {
						auto mp = socket_to_buffer.find(list_sockets[i]);
						std::cout << msg << " ++ to socket = " << list_sockets[i] << "; buffer = " << mp->second << ";\n";
						bufferevent_write(mp->second, msg.data(), strlen(msg.data()));
						//bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
					}

					el->player1_id = pending_lobbies[pending_lobbies.size() - 1]->player1_id;
					el->player2_id = pending_lobbies[pending_lobbies.size() - 1]->player2_id;
					el->lobby_name = pending_lobbies[pending_lobbies.size() - 1]->lobby_name;
					delete pending_lobbies[pending_lobbies.size() - 1];
					pending_lobbies.pop_back();
					break;
				}
			}
			break;
		default:
			std::cout << "BAD COMMAND\n";
			std::cout << current_command << std::endl;
			break;
		}
	}

	//bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
	delete[] data;
}