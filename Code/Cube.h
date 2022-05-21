#pragma once

#include "IntVector3.h"

class Cube
{
public:
	Cube() = default;
	Cube(const IntVector3& min, const IntVector3& max)
		: min(min), max(max)
	{}

	long long int Volume() const
	{
		return static_cast<long long int>(max.x - min.x + 1)
			* static_cast<long long int>(max.y - min.y + 1)
			* static_cast<long long int>(max.z - min.z + 1);
	}

private:
	IntVector3 min{};
	IntVector3 max{};
};
