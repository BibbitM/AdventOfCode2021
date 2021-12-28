#include "pch.h"

#include <istream>
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
