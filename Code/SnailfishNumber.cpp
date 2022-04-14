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
		else while (std::isdigit(*begin))
		{
			left *= 10;
			left += *begin++ - '0';
		}
		assert(*begin == ','); ++begin;
		int right{};
		std::unique_ptr<Number> rightPtr{};
		if (*begin == '[')
		{
			rightPtr = std::unique_ptr<Number>(new Number(begin, end));
		}
		else while (std::isdigit(*begin))
		{
			right *= 10;
			right += *begin++ - '0';
		}
		assert(*begin == ']'); ++begin;

		assert(begin <= end);

		*this = Number(left, std::move(leftPtr), right, std::move(rightPtr));
	}

	Number::Number(int left, std::unique_ptr<Number> leftPtr, int right, std::unique_ptr<Number> rightPtr)
		: m_left(left), m_leftPtr(std::move(leftPtr))
		, m_right(right), m_rightPtr(std::move(rightPtr))
	{
		Reduce();
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

	std::string Number::ToString() const
	{
		std::string str;
		str.reserve(100);
		ToString(str);
		return str;
	}

	void Number::ToString(std::string& outStr) const
	{
		outStr += '[';
		if (m_leftPtr)
			m_leftPtr->ToString(outStr);
		else
			outStr += std::to_string(m_left);
		outStr += ',';
		if (m_rightPtr)
			m_rightPtr->ToString(outStr);
		else
			outStr += std::to_string(m_right);
		outStr += ']';
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

	void Number::Reduce()
	{
		while (ReduceNumber(0) != nullptr || Split()) { /* do nothing */ }
	}

	std::unique_ptr<Number> Number::ReduceNumber(int level)
	{
		++level;

		if (level >= c_reduceAtLevel)
		{
			if (m_leftPtr && !m_leftPtr->m_leftPtr && !m_leftPtr->m_rightPtr)
			{
				m_left = 0;
				if (m_rightPtr)
				{
					m_rightPtr->AddRightToLeft(m_leftPtr.get());
				}
				else
				{
					m_right += m_leftPtr->m_right;
					m_leftPtr->m_right = 0;
				}
				return std::move(m_leftPtr);
			}
			else if (m_rightPtr && !m_rightPtr->m_leftPtr && !m_rightPtr->m_rightPtr)
			{
				m_right = 0;
				if (m_leftPtr)
				{
					m_leftPtr->AddLeftToRight(m_rightPtr.get());
				}
				else
				{
					m_left += m_rightPtr->m_left;	
					m_rightPtr->m_left = 0;
				}
				return std::move(m_rightPtr);
			}
		}

		if (m_leftPtr)
		{
			if (auto leftReduced = m_leftPtr->ReduceNumber(level))
			{
				if (m_rightPtr)
				{
					m_rightPtr->AddRightToLeft(leftReduced.get());
				}
				else
				{
					m_right += leftReduced->m_right;
					leftReduced->m_right = 0;
				}
				return leftReduced;
			}
		}

		if (m_rightPtr)
		{
			if (auto rightReduced = m_rightPtr->ReduceNumber(level))
			{
				if (m_leftPtr)
				{
					m_leftPtr->AddLeftToRight(rightReduced.get());
				}
				else
				{
					m_left += rightReduced->m_left;
					rightReduced->m_left = 0;
				}
				return rightReduced;
			}
		}

		return {};
	}

	void Number::AddRightToLeft(Number* number)
	{
		if (m_leftPtr)
			m_leftPtr->AddRightToLeft(number);
		else
		{
			m_left += number->m_right;
			number->m_right = 0;
		}
	}

	void Number::AddLeftToRight(Number* number)
	{
		if (m_rightPtr)
			m_rightPtr->AddLeftToRight(number);
		else
		{
			m_right += number->m_left;
			number->m_left = 0;
		}
	}

	bool Number::Split()
	{
		if (m_leftPtr && m_leftPtr->Split())
			return true;

		if (!m_leftPtr && m_left >= c_minToSplit)
		{
			m_leftPtr = std::unique_ptr<Number>(new Number(m_left / 2, m_left - m_left / 2));
			m_left = 0;
			return true;
		}

		if (m_rightPtr && m_rightPtr->Split())
			return true;

		if (!m_rightPtr && m_right >= c_minToSplit)
		{
			m_rightPtr = std::unique_ptr<Number>(new Number(m_right / 2, m_right - m_right / 2));
			m_right = 0;
			return true;
		}

		return false;
	}

	Number operator+(const Number& left, const Number& right)
	{
		return Number(0, std::unique_ptr<Number>(new Number(left)), 0, std::unique_ptr<Number>(new Number(right)));
	}
}
