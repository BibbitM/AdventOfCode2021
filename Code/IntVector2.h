#pragma once

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
