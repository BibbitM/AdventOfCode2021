#pragma once

#include <istream>

struct IntVector2
{
	int x;
	int y;

	// Since C++20 we have default comparison - https://en.cppreference.com/w/cpp/language/default_comparisons
	bool operator==(const IntVector2& other) const = default;
	// So I don't need to write the below code :).
	//bool operator==(const IntVector2& other) const
	//{
	//	return x == other.x && y == other.y;
	//}
	//
	//bool operator!=(const IntVector2& other) const
	//{
	//	// return !(*this == other); Which looks better? :thinking_face:
	//	return !operator==(other);
	//}

	IntVector2& operator+=(const IntVector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
};

inline std::istream& operator>>(std::istream& in, IntVector2& vec)
{
	in >> vec.x;
	in.ignore(1, ',');
	in >> vec.y;
	return in;
}

template<>
struct std::hash<IntVector2>
{
	std::size_t operator()(const IntVector2& vec) const noexcept
	{
		std::size_t hx = std::hash<int>{}(vec.x);
		std::size_t hy = std::hash<int>{}(vec.y);
		return hx ^ (hy << 1);
	}
};
