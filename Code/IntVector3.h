#pragma once

#include <istream>

struct IntVector3
{
	int x;
	int y;
	int z;

	bool operator==(const IntVector3& other) const = default;
};

inline int Distance2(const IntVector3& a, const IntVector3& b)
{
	auto sqr = [](int val) { return val * val; };
	return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

inline std::istream& operator>>(std::istream& in, IntVector3& vec)
{
	in >> vec.x;
	in.ignore(1, ',');
	in >> vec.y;
	in.ignore(1, ',');
	in >> vec.z;
	return in;
}
