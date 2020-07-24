#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include <string>
#include "tcp_client.hpp"

extern struct Settings
{
	std::string host;
	tcp_client client;

	void save();
	void load();
} settings;

#endif