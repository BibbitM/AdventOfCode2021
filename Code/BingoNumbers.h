#pragma once

#include <istream>
#include <vector>

class BingoNumbers
{
public:
	const std::vector<int>& AsVector() const { return m_numbers; }

private:
	friend std::istream& operator>>(std::istream& in, BingoNumbers& numbers);

	std::vector<int> m_numbers;
};

std::istream& operator>>(std::istream& in, BingoNumbers& numbers);
