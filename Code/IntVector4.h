#pragma once

struct IntVector4
{
	int x;
	int y;
	int z;
	int w;

	bool operator==(const IntVector4& other) const = default;
};
