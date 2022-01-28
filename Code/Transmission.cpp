#include "pch.h"
#include "Transmission.h"

#include <cassert>

unsigned int Transmission::ReadBits(size_t bitsCount)
{
	unsigned int value{};
	for (unsigned int b = 0; b < bitsCount; ++b, ++m_position)
	{
		value <<= 1u;
		value |= m_bits[m_position] ? 1u : 0u;
	}
	return value;
}

std::istream& operator>>(std::istream& in, Transmission& transmission)
{
	std::string line;
	in >> line;
	transmission.m_bits.reserve(transmission.m_bits.size() + line.length() * 4u);
	for (char hex : line)
	{
		assert(hex >= '0' && hex <= '9' || hex >= 'A' && hex <= 'F');
		unsigned int value = (hex >= '0' && hex <= '9') ? hex - '0' : hex - 'A' + 10;
		for (unsigned int b = 0; b < 4; ++b)
		{
			transmission.m_bits.push_back((value & (1u << ((4u - 1u) - b))) != 0);
		}
	}
	return in;
}
