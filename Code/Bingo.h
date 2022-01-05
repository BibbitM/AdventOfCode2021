#pragma once

#include <array>
#include <initializer_list>

template<class T>
concept TwoDimensionArray = requires(T t)
{
	{ std::begin(t) };
	{ std::end(t)  };
	{ std::begin(*std::begin(t)) };
	{ std::end(*std::begin(t)) };
};

class Bingo
{
public:
	static constexpr size_t SIZE = 5;
	static constexpr int MATCHED_VALUE = -1;

	Bingo() : m_values{} { }
	template<TwoDimensionArray T>
	Bingo(T&& initialValues);

	bool Check(int value) const;
	bool Match(int value);
	int SumOfUnmatched() const;

private:
	std::array<std::array<int, SIZE>, SIZE > m_values;
};

template<TwoDimensionArray T>
Bingo::Bingo(T&& initialValues)
	: m_values{}
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
