#include <string>
#include <vector>
#include <cctype>

class Servercmd
{
	std::vector<std::string> v;
public:
	Servercmd(const std::string& s)
	{
		bool white = true;
		for (int i = 0; s[i] < s.length(); i++)
		{
			if (white)
			{
				if (!isspace(s[i]))
				{
					v.push_back(std::string(1, s[i]));
					white = false;
				}
			}
			else {
				if (isspace(s[i]))
					white = true;
				else
					v[v.size() - 1] += s[i];
			}
		}
	}

	std::string operator[](unsigned int i)
	{
		if (i < v.size())
			return v[i];
		else
			return "";
	}
};