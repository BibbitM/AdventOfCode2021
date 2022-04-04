#pragma once

namespace Snailfish
{
	class Number
	{
	public:
		Number() {}
		Number(int left, int right) : m_left(left), m_right(right) {}
		int Magnitude() const { return m_left * 3 + m_right * 2; }

	private:
		int m_left{};
		int m_right{};
	};
}
