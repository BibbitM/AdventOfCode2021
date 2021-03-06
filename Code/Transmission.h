#pragma once

#include <istream>
#include <vector>

class Transmission
{
public:
	size_t GetLength() const { return m_bits.size(); }
	size_t GetPosition() const { return m_position; }
	unsigned int ReadBits(size_t bitsCount);
	void Reset() { m_position = 0; }

private:
	std::vector<bool> m_bits;
	size_t m_position{};

	friend std::istream& operator>>(std::istream& in, Transmission& transmission);
};

unsigned int ReadPacketVersion(Transmission& transmision);
unsigned long long int ReadPacketValue(Transmission& transmision);

std::istream& operator>>(std::istream& in, Transmission& transmission);
