#include "pch.h"

#include <cassert>
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

int GetGammaRate(const std::vector<int>& numbers, int bits)
{
	assert(bits > 0);
	assert(bits < sizeof(int) * 8);

	std::vector<int> bitCounts;
	bitCounts.resize(bits);

	for (int num : numbers)
	{
		for (int b = 0; b < bits; ++b)
		{
			bitCounts[b] += ((num & (1 << b)) != 0) ? 1 : -1;
		}
	}

	int value = 0;
	for (int b = 0; b < bits; ++b)
	{
		value += (bitCounts[b] > 0) ? (1 << b) : 0;
	}

	return value;
}

int GetEpsilonRate(const std::vector<int>& numbers, int bits)
{
	assert(bits > 0);
	assert(bits < sizeof(int) * 8);

	std::vector<int> bitCounts;
	bitCounts.resize(bits);

	for (int num : numbers)
	{
		for (int b = 0; b < bits; ++b)
		{
			bitCounts[b] += ((num & (1 << b)) != 0) ? 1 : -1;
		}
	}

	int value = 0;
	for (int b = 0; b < bits; ++b)
	{
		value += (bitCounts[b] < 0) ? (1 << b) : 0; //< Using "<" instead of ">" in GetGammaRate. If changed to "<=" then we could use negated GetGammaRate.
	}

	return value;
	// return (~GetGammaRate(numbers, bits) & ~(~0 << bits));
}

int64_t GetPowerConsumption(const std::vector<int>& numbers, int bits)
{
	return static_cast<int64_t>(GetGammaRate(numbers, bits)) * static_cast<int64_t>(GetEpsilonRate(numbers, bits));
}
