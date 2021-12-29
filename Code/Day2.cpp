#include "pch.h"

#include "IntVector2.h"
#include <istream>
#include <vector>

std::vector<IntVector2> LoadSubmarineCommandsStream(std::istream& in)
{
	std::vector<IntVector2> commands;
	std::string cmd;
	int value;
	while (in >> cmd >> value)
	{
		if (cmd == "down")
			commands.push_back({ 0, value });
		if (cmd == "up")
			commands.push_back({ 0, -value });
		if (cmd == "forward")
			commands.push_back({ value, 0 });
		//in.ignore(); //< Skip endl. Not needed.
	}
	return commands;
}
