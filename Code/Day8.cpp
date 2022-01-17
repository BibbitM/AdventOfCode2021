#include "pch.h"

#include <array>
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

std::istream& GetBitsCodeAndMessage(std::istream& input, std::vector<uint32_t>& code, std::vector<uint32_t>& message)
{
	code.clear();
	message.clear();

	std::string line;
	std::getline(input, line);

	std::istringstream lineInput(line);
	std::string signal;
	while (lineInput >> signal && signal != "|")
	{
		code.push_back(GetBitsFromSignal(signal));
	}
	while (lineInput >> signal)
	{
		message.push_back(GetBitsFromSignal(signal));
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

std::array<uint32_t, 10> CreateDecoderFromTestSignal(const std::vector<uint32_t>& code)
{
	std::array<uint32_t, 10> decoder{};
	// Get simple numbers
	for (uint32_t num : code)
	{
		switch (std::popcount(num))
		{
		case 2: decoder[1] = num; break;
		case 3: decoder[7] = num; break;
		case 4: decoder[4] = num; break;
		case 7: decoder[8] = num; break;
		}
	}

	// Get 0
	const uint32_t zeroMask = decoder[4] & ~decoder[1];
	for (uint32_t num : code)
	{
		if (std::popcount(num) == 6 && std::popcount(num & zeroMask) == 1)
			decoder[0] = num;
	}
	// Get rest of 6 bit numbers
	for (uint32_t num : code)
	{
		if (std::popcount(num) == 6 && num != decoder[0])
		{
			switch (std::popcount(num & decoder[1]))
			{
			case 1: decoder[6] = num; break;
			case 2: decoder[9] = num; break;
			}
		}
	}

	// Get 5bit numbers
	for (uint32_t num : code)
	{
		if (std::popcount(num) == 5)
		{
			if (std::popcount(num & decoder[1]) == 2)
				decoder[3] = num;
			else switch (std::popcount(num & decoder[6]))
			{
			case 4: decoder[2] = num; break;
			case 5: decoder[5] = num; break;
			}
		}
	}

	return decoder;
}

uint32_t DecodeMessage(const std::array<uint32_t, 10>& decoder, const std::vector<uint32_t>& message)
{
	uint32_t decoded = 0;
	for (uint32_t signal : message)
	{
		for (uint32_t num = 0; num < std::size(decoder); ++num)
		{
			if (signal == decoder[num])
			{
				decoded = decoded * 10 + num;
			}
		}
	}
	return decoded;
}