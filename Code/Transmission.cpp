#include "pch.h"
#include "Transmission.h"

#include <cassert>

namespace
{
	constexpr unsigned int c_literalValueType = 4u;
}

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

unsigned int ReadPacketVersion(Transmission& transmision)
{
	unsigned int ver = transmision.ReadBits(3);
	unsigned int type = transmision.ReadBits(3);
	if (type == c_literalValueType)
	{
		bool hasNext = true;
		while (hasNext)
		{
			hasNext = transmision.ReadBits(1) != 0;
			transmision.ReadBits(4); //< Skip number.
		}
	}
	else if (transmision.ReadBits(1) == 0)
	{
		const unsigned int subPacketLength = transmision.ReadBits(15);
		const size_t endPosition = transmision.GetPosition() + subPacketLength;
		while (transmision.GetPosition() < endPosition)
		{
			ver += ReadPacketVersion(transmision);
		}
	}
	else
	{
		const unsigned int supPacketsCount = transmision.ReadBits(11);
		for (unsigned int i = 0; i < supPacketsCount; ++i)
		{
			ver += ReadPacketVersion(transmision);
		}
	}
	return ver;
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
