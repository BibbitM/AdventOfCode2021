#pragma once

#include <istream>
#include <vector>

class Transmission
{
public:
	size_t GetLength() const { return m_bits.size(); }
	unsigned int ReadBits(size_t bitsCount);

private:
	std::vector<bool> m_bits;
	size_t m_position{};

	friend std::istream& operator>>(std::istream& in, Transmission& transmission);
};

std::istream& operator>>(std::istream& in, Transmission& transmission);
