#include "pch.h"

#include "BingoNumbers.h"

#include <sstream>
#include <string>

std::istream& operator>>(std::istream& in, BingoNumbers& numbers)
{
	std::string line;
	if (std::getline(in, line))
	{
		std::istringstream istream(line);

		int number{};
		while (istream >> number)
		{
			numbers.m_numbers.push_back(number);
			istream.ignore();
		}
	}
	return in;
}
