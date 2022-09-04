#pragma once

struct IntVector4
{
	int x;
	int y;
	int z;
	int w;

	bool operator==(const IntVector4& other) const = default;
	int& operator[](size_t coord) { return (&x)[coord]; }
	int operator[](size_t coord) const { return (&x)[coord]; }
};
