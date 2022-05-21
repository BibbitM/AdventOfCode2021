#pragma once

#include "IntVector3.h"

class Cube
{
public:
	Cube() = default;
	Cube(const IntVector3& min, const IntVector3& max)
		: min(min), max(max)
	{}

	int Volume() const
	{
		return (max.x - min.x + 1) * (max.y - min.y + 1) * (max.z - min.z + 1);
	}

private:
	IntVector3 min{};
	IntVector3 max{};
};
