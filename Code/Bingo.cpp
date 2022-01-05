#include "pch.h"

#include "Bingo.h"

#include <cassert>

Bingo::Bingo(std::initializer_list<std::initializer_list<int>> initialValues)
{
	assert(initialValues.size() == SIZE);
	auto rowIt = initialValues.begin();

	for (size_t row = 0; row < SIZE; ++row, ++rowIt)
	{
		assert(rowIt->size() == SIZE);
		auto colIt = rowIt->begin();
		for (size_t col = 0; col < SIZE; ++col, ++colIt)
		{
			m_values[row][col] = *colIt;
		}
	}
}

Bingo::Bingo(const int(&initialValues)[5][5])
{
	for (size_t row = 0; row < SIZE; ++row)
	{
		for (size_t col = 0; col < SIZE; ++col)
		{
			m_values[row][col] = initialValues[row][col];
		}
	}
}

bool Bingo::Check(int value) const
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

bool Bingo::Match(int value)
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

int Bingo::SumOfUnmatched() const
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
