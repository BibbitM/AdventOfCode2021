#pragma once

#include <memory>
#include <string_view>

namespace Snailfish
{
	class Number
	{
	public:
		Number() {}
		Number(int left, int right) : m_left(left), m_right(right) {}
		Number(std::string_view number);

		int Magnitude() const;

		bool operator==(const Number& other) const;

		friend Number operator+(const Number& left, const Number& right);

	private:
		Number(const char*& begin, const char* end);
		Number(int left, std::unique_ptr<Number> leftPtr, int right, std::unique_ptr<Number> rightPtr);
		Number(const Number& other);
		Number& operator=(Number&& other) = default;

		int m_left{};
		int m_right{};
		std::unique_ptr<Number> m_leftPtr;
		std::unique_ptr<Number> m_rightPtr;
	};
}
