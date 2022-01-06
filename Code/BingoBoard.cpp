#include "pch.h"

#include "BingoBoard.h"

bool BingoBoard::Check(int value) const
{
	for (size_t row = 0; row < SIZE; ++row)
	{
		for (size_t col = 0; col < SIZE; ++col)
		{
			if (m_values[row][col] == value)
				return true;
		}
	}
	return false;
}

bool BingoBoard::Match(int value)
{
	for (size_t row = 0; row < SIZE; ++row)
	{
		for (size_t col = 0; col < SIZE; ++col)
		{
			if (m_values[row][col] == value)
			{
				m_values[row][col] = MATCHED_VALUE;

				bool allMatched = true;
				for (size_t c = 0; c < SIZE; ++c)
				{
					if (m_values[row][c] != MATCHED_VALUE)
					{
						allMatched = false;
						break;
					}
				}
				if (allMatched)
					return true;

				allMatched = true;
				for (size_t r = 0; r < SIZE; ++r)
				{
					if (m_values[r][col] != MATCHED_VALUE)
					{
						allMatched = false;
						break;
					}
				}
				return allMatched;
			}
		}
	}
	return false;
}

int BingoBoard::SumOfUnmatched() const
{
	int sum = 0;
	for (size_t row = 0; row < SIZE; ++row)
	{
		for (size_t col = 0; col < SIZE; ++col)
		{
			if (m_values[row][col] != MATCHED_VALUE)
				sum += m_values[row][col];
		}
	}
	return sum;
}

std::istream& operator>>(std::istream& in, BingoBoard& board)
{
	for (size_t row = 0; row < BingoBoard::SIZE; ++row)
	{
		for (size_t col = 0; col < BingoBoard::SIZE; ++col)
		{
			in >> board.m_values[row][col];
		}
	}

	return in;
}
