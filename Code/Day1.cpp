#include "pch.h"

#include <istream>
#include <limits>
#include <string>
#include <vector>

std::vector<int> LoadIntStream(std::istream& in)
{
	std::vector<int> intVector;
	std::string line;
	while (std::getline(in, line))
	{
		intVector.push_back(std::stoi(line));
	}
	return intVector;
}

int GetIncreasedMeasurements(std::vector<int> measurements)
{
	int prevM = std::numeric_limits<int>::max();
	int increased = 0;
	for (int m : measurements)
	{
		if (m > prevM)
			++increased;
		prevM = m;
	}
	return increased;
}