#pragma once

#include <string_view>

namespace Snailfish
{
	class Number
	{
	public:
		Number() {}
		Number(int left, int right) : m_left(left), m_right(right) {}
		Number(std::string_view number);
		int Magnitude() const { return m_left * 3 + m_right * 2; }

		bool operator==(const Number& other) const = default;

	private:
		int m_left{};
		int m_right{};
	};
}
