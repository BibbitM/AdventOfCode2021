#include "pch.h"
#include "Transmission.h"

#include <algorithm>
#include <cassert>
#include <limits>

namespace
{
	constexpr unsigned int c_literalValueType = 4u;

	constexpr unsigned int c_operatorSumType = 0u;
	constexpr unsigned int c_operatorProductType = 1u;
	constexpr unsigned int c_operatorMinimumType = 2u;
	constexpr unsigned int c_operatorMaximumType = 3u;
	constexpr unsigned int c_operatorGreaterType = 5u;
	constexpr unsigned int c_operatorLessType = 6u;
	constexpr unsigned int c_operatorEqualType = 7u;

	enum class PacketType : unsigned int
	{
		LiteralValue = 4u,
		OperatorSum = 0u,
		OperatorProduct = 1u,
		OperatorMinimum = 2u,
		OperatorMaximum = 3u,
		OperatorGreater = 5u,
		OperatorLess = 6u,
		OperatorEqual = 7u,
	};
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
	PacketType type = static_cast<PacketType>(transmision.ReadBits(3));
	if (type == PacketType::LiteralValue)
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

unsigned long long int ReadPacketValue(Transmission& transmision)
{
	transmision.ReadBits(3); //< Skip version.
	PacketType type = static_cast<PacketType>(transmision.ReadBits(3));
	if (type == PacketType::LiteralValue)
	{
		unsigned long long int value{};
		bool hasNext = true;
		while (hasNext)
		{
			hasNext = transmision.ReadBits(1) != 0;
			value <<= 4u;
			value |= transmision.ReadBits(4);
		}
		return value;
	}
	else
	{
		std::vector<unsigned long long int> values;
		if (transmision.ReadBits(1) == 0)
		{
			const unsigned int subPacketLength = transmision.ReadBits(15);
			const size_t endPosition = transmision.GetPosition() + subPacketLength;
			while (transmision.GetPosition() < endPosition)
			{
				values.push_back(ReadPacketValue(transmision));
			}
		}
		else
		{
			const unsigned int supPacketsCount = transmision.ReadBits(11);
			values.reserve(supPacketsCount);
			for (unsigned int i = 0; i < supPacketsCount; ++i)
			{
				values.push_back(ReadPacketValue(transmision));
			}
		}

		unsigned long long int result{};
		switch (type)
		{
		case PacketType::OperatorSum:
			result = 0;
			for (unsigned long long int val : values)
				result += val;
			break;
		case PacketType::OperatorProduct:
			result = 1;
			for (unsigned long long int val : values)
				result *= val;
			break;
		case PacketType::OperatorMinimum:
			result = std::numeric_limits<unsigned int>::max();
			for (unsigned long long int val : values)
				result = std::min(val, result);
			break;
		case PacketType::OperatorMaximum:
			result = std::numeric_limits<unsigned int>::min();
			for (unsigned long long int val : values)
				result = std::max(val, result);
			break;
		case PacketType::OperatorGreater:
			assert(values.size() == 2);
			result = values[0] > values[1];
			break;
		case PacketType::OperatorLess:
			assert(values.size() == 2);
			result = values[0] < values[1];
			break;
		case PacketType::OperatorEqual:
			assert(values.size() == 2);
			result = values[0] == values[1];
			break;
		}
		return result;
	}
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
