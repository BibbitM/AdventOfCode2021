#include "pch.h"

#include "SnailfishNumber.h"

#include <cassert>
#include <sstream>

Snailfish::Number::Number(std::string_view number)
	: Number()
{
	assert(number.size() >= 5);
	const char* ptr = number.data();
	++ptr; //< Skip "["
	m_left = *ptr++ - '0';
	++ptr; //< Skip ","
	m_right = *ptr++ - '0';
	++ptr; //< Skip "]"
	assert(ptr == number.data() + number.size());
}
