#include "pch.h"

#include "IntVector2.h"
#include <istream>
#include <cmath>
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

int GetSubmarineMultipliedPosition(const std::vector<IntVector2>& commands)
{
	IntVector2 position{};

	for (const IntVector2& cmd : commands)
	{
		position += cmd;
	}

	return std::abs(position.x * position.y);
}
