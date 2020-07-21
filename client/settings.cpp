#include "settings.hpp"
#include <fstream>

Settings settings;
static const char path[] = "DATA/settings.dat";

void Settings::save()
{
	std::ofstream file(path);
	file << host;
}

void Settings::load()
{
	try
	{
		std::ifstream file(path);
		file >> host;
	}
	catch (...)
	{
		host = "";
	}
}