#pragma once

#include <array>
#include <initializer_list>
#include <istream>

template<class T>
concept TwoDimensionArray = requires(T t)
{
	{ std::begin(t) };
	{ std::end(t)  };
	{ std::begin(*std::begin(t)) };
	{ std::end(*std::begin(t)) };
};

class BingoBoard //< TODO: rename to BingoBoard (and the file)
{
public:
	static constexpr size_t SIZE = 5;
	static constexpr int MATCHED_VALUE = -1;

	BingoBoard() : m_values{}, m_win{ false } { }
	template<TwoDimensionArray T>
	BingoBoard(T&& initialValues);

	bool operator==(const BingoBoard&) const = default;

	bool Check(int value) const;
	bool Match(int value);
	int SumOfUnmatched() const;

private:
	friend std::istream& operator>>(std::istream& in, BingoBoard& board);

	std::array<std::array<int, SIZE>, SIZE > m_values;
	bool m_win;
};

template<TwoDimensionArray T>
BingoBoard::BingoBoard(T&& initialValues)
	: BingoBoard{}
{
	auto rowIt = std::begin(initialValues);
	const auto rowEndIt = std::end(initialValues);
	for (size_t row = 0; row < SIZE && rowIt != rowEndIt; ++row, ++rowIt)
	{
		auto colIt = std::begin(*rowIt);
		const auto colEndIt = std::end(*rowIt);
		for (size_t col = 0; col < SIZE && colIt != colEndIt; ++col, ++colIt)
		{
			m_values[row][col] = *colIt;
		}
	}
}

std::istream& operator>>(std::istream& in, BingoBoard& board);
