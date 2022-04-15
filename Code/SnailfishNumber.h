#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace Snailfish
{
	class Number
	{
	public:
		static constexpr int c_reduceAtLevel = 4;
		static constexpr int c_minToSplit = 10;

		Number() {}
		Number(int left, int right) : m_left(left), m_right(right) {}
		Number(std::string_view number);
		Number(const Number& other);
		Number& operator=(Number&& other) = default;

		int Magnitude() const;

		bool operator==(const Number& other) const;

		friend Number operator+(const Number& left, const Number& right);
		std::string ToString() const;
		void ToString(std::string& outStr) const;

	private:
		Number(const char*& begin, const char* end);
		Number(int left, std::unique_ptr<Number> leftPtr, int right, std::unique_ptr<Number> rightPtr);

		void Reduce();
		std::unique_ptr<Number> ReduceNumber(int level);
		void AddRightToLeft(Number* number);
		void AddLeftToRight(Number* number);

		bool Split();

		int m_left{};
		int m_right{};
		std::unique_ptr<Number> m_leftPtr;
		std::unique_ptr<Number> m_rightPtr;
	};
}

inline Snailfish::Number operator "" _SN(const char* str, size_t len)
{
	return Snailfish::Number({ str, len });
}
