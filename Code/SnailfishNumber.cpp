#include "pch.h"

#include "SnailfishNumber.h"

#include <cassert>
#include <sstream>

namespace Snailfish
{
	typedef const char* ptr;

	Number::Number(std::string_view number)
	{
		const char* begin = number.data();
		const char* end = number.data() + number.size();
		*this = Number(begin, end);
	}

	Number::Number(const char*& begin, const char* end)
	{
		assert(std::distance(begin, end) >= 5);

		assert(*begin == '['); ++begin;
		int left{};
		std::unique_ptr<Number> leftPtr{};
		if (*begin == '[')
		{
			// Cannot use std::make_unique as the Ctor is private
			// (see https://stackoverflow.com/questions/65286678/make-unique-cannot-access-private-constructor-in-static-member)
			leftPtr = std::unique_ptr<Number>(new Number(begin, end));
		}
		else
		{
			left = *begin++ - '0';
		}
		assert(*begin == ','); ++begin;
		int right{};
		std::unique_ptr<Number> rightPtr{};
		if (*begin == '[')
		{
			rightPtr = std::unique_ptr<Number>(new Number(begin, end));
		}
		else
		{
			right = *begin++ - '0';
		}
		assert(*begin == ']'); ++begin;

		assert(begin <= end);

		*this = Number(left, std::move(leftPtr), right, std::move(rightPtr));
	}

	Number::Number(int left, std::unique_ptr<Number> leftPtr, int right, std::unique_ptr<Number> rightPtr)
		: m_left(left), m_leftPtr(std::move(leftPtr))
		, m_right(right), m_rightPtr(std::move(rightPtr))
	{
	}

	Number::Number(const Number& other)
		: m_left(other.m_left), m_leftPtr(other.m_leftPtr ? std::unique_ptr<Number>(new Number(*other.m_leftPtr)) : nullptr)
		, m_right(other.m_right), m_rightPtr(other.m_rightPtr ? std::unique_ptr<Number>(new Number(*other.m_rightPtr)) : nullptr)
	{
	}

	int Number::Magnitude() const
	{
		return (m_leftPtr ? m_leftPtr->Magnitude() : m_left) * 3 + (m_rightPtr ? m_rightPtr->Magnitude() : m_right) * 2;
	}

	bool Number::operator==(const Number& other) const
	{
		bool leftEqual = false;
		if (m_leftPtr && other.m_leftPtr)
		{
			leftEqual = *m_leftPtr == *other.m_leftPtr;
		}
		else if (!m_leftPtr && !other.m_leftPtr)
		{
			leftEqual = m_left == other.m_left;
		}

		bool rightEqual = false;
		if (m_rightPtr && other.m_rightPtr)
		{
			rightEqual = *m_rightPtr == *other.m_rightPtr;
		}
		else if (!m_rightPtr && !other.m_rightPtr)
		{
			rightEqual = m_right == other.m_right;
		}

		return leftEqual && rightEqual;
	}

	Number operator+(const Number & left, const Number & right)
	{
		return Number(0, std::unique_ptr<Number>(new Number(left)), 0, std::unique_ptr<Number>(new Number(right)));
	}
}
