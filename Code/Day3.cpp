#include "pch.h"

#include <istream>
#include <string>
#include <vector>

std::vector<int> LoadBinaryStream(std::istream& in)
{
	std::string line;
	std::vector<int> numbers;
	while (std::getline(in, line))
	{
		numbers.push_back(std::stoi(line, nullptr, 2));
	}
	return numbers;
}
