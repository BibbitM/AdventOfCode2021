#pragma once

#include "IntVector3.h"

#include <vector>

class Cube
{
public:
	Cube() = default;
	constexpr Cube(const IntVector3& min, const IntVector3& max)
		: min(min), max(max)
	{}

	bool operator==(const Cube& other) const = default;

	long long int Volume() const
	{
		return static_cast<long long int>(max.x - min.x + 1)
			* static_cast<long long int>(max.y - min.y + 1)
			* static_cast<long long int>(max.z - min.z + 1);
	}

	Cube Intersection(const Cube& other) const;

	friend std::istream& operator>>(std::istream& in, Cube& cube);

private:
	IntVector3 min{};
	IntVector3 max{};
};

std::istream& operator>>(std::istream& in, Cube& cube);

class CubeMap
{
public:
	void On(const Cube& cube) { OnOff(cube, true); }
	void Off(const Cube& cube) { OnOff(cube, false); }

	long long int Volume() const;

private:
	void OnOff(const Cube& cube, bool addNewCube);

	std::vector<Cube> onCubes;
	std::vector<Cube> offCubes;
};
