#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#include <string>

extern struct Settings
{
	std::string host;

	void save();
	void load();
} settings;

#endif