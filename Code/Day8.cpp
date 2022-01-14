#include "pch.h"

#include <bit>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

uint32_t GetBitsFromSignal(const std::string& signal)
{
	uint32_t bits = 0;
	for (char c : signal)
		bits |= 1u << static_cast<uint32_t>(c - 'a');
	return bits;
}

std::istream& GetBitsAfterSeparator(std::istream& input, std::vector<uint32_t>& bits)
{
	bits.clear();

	std::string line;
	std::getline(input, line);

	std::istringstream lineInput(line);
	lineInput.ignore(std::numeric_limits<std::streamsize>::max(), '|');
	std::string signal;
	while (lineInput >> signal)
	{
		bits.push_back(GetBitsFromSignal(signal));
	}

	return input;
}

int CountNumbersWith2347Bits(const std::vector<uint32_t>& numbers)
{
	int count = 0;
	for (uint32_t num : numbers)
	{
		switch (std::popcount(num))
		{
		case 2:
		case 3:
		case 4:
		case 7:
			++count;
			break;
		}
	}
	return count;
}
