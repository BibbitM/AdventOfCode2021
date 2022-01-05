#pragma once

#include <array>
#include <initializer_list>

class Bingo
{
public:
	static constexpr size_t SIZE = 5;
	static constexpr int MATCHED_VALUE = -1;

	Bingo() : m_values{} { }
	Bingo(std::initializer_list<std::initializer_list<int>> initialValues);
	Bingo(const int (&initialValues)[5][5]);

	bool Check(int value) const;
	bool Match(int value);
	int SumOfUnmatched() const;

private:
	std::array<std::array<int, SIZE>, SIZE > m_values;
};
