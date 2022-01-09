#pragma once

#include "IntVector2.h"

#include <istream>

struct IntLine2
{
	IntVector2 first;
	IntVector2 second;

	bool operator==(const IntLine2& other) const = default;
};

inline std::istream& operator>>(std::istream& in, IntLine2& line)
{
	in >> line.first;
	in.ignore(4, '>');
	in >> line.second;
	return in;
}
