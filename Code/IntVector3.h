#pragma once

#include <cmath>
#include <istream>

struct IntVector3
{
	int x;
	int y;
	int z;

	bool operator==(const IntVector3& other) const = default;
	int operator[](size_t coord) const { return (&x)[coord]; }
};

inline IntVector3 operator+(const IntVector3& a, const IntVector3& b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

inline IntVector3 operator-(const IntVector3& a, const IntVector3& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

inline int Distance2(const IntVector3& a, const IntVector3& b)
{
	auto sqr = [](int val) { return val * val; };
	return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

inline int ManhattanDistance(const IntVector3& a, const IntVector3& b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
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
