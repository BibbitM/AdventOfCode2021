#include "pch.h"
#include "Cube.h"

#include <numeric>

std::istream& operator>>(std::istream& in, Cube& cube)
{
	//                     x=10..12,y=10..12,z=10..12
	in.ignore(3, '='); //  x=
	in >> cube.min.x;  //    10
	in.ignore(2);      //      ..
	in >> cube.max.x;  //        12
	in.ignore(3, '='); //          ,y=
	in >> cube.min.y;  //             10
	in.ignore(2);      //               ..
	in >> cube.max.y;  //                 12
	in.ignore(3, '='); //                   ,z=
	in >> cube.min.z;  //                      10
	in.ignore(2);      //                        ..
	in >> cube.max.z;  //                          12
	return in;
}

Cube Cube::Intersection(const Cube& other) const
{
	Cube intersection;

	intersection.min.x = std::max(min.x, other.min.x);
	intersection.min.y = std::max(min.y, other.min.y);
	intersection.min.z = std::max(min.z, other.min.z);

	intersection.max.x = std::min(max.x, other.max.x);
	intersection.max.y = std::min(max.y, other.max.y);
	intersection.max.z = std::min(max.z, other.max.z);

	intersection.max.x = std::max(intersection.max.x, intersection.min.x - 1);
	intersection.max.y = std::max(intersection.max.y, intersection.min.y - 1);
	intersection.max.z = std::max(intersection.max.z, intersection.min.z - 1);

	return intersection;
}

void CubeMap::On(const Cube& cube)
{
	std::vector<Cube> newOnCubes;
	newOnCubes.push_back(cube);
	std::vector<Cube> newOffCubes;

	for (const Cube& onC : onCubes)
	{
		Cube offC = cube.Intersection(onC);
		if (offC.Volume())
			newOffCubes.push_back(offC);
	}

	for (const Cube& offC : offCubes)
	{
		Cube onC = cube.Intersection(offC);
		if (onC.Volume())
			newOnCubes.push_back(onC);
	}

	onCubes.insert(onCubes.end(), newOnCubes.begin(), newOnCubes.end());
	offCubes.insert(offCubes.end(), newOffCubes.begin(), newOffCubes.end());
}

void CubeMap::Off(const Cube& cube)
{
	std::vector<Cube> newOnCubes;
	std::vector<Cube> newOffCubes;

	for (const Cube& onC : onCubes)
	{
		Cube offC = cube.Intersection(onC);
		if (offC.Volume())
			newOffCubes.push_back(offC);
	}

	for (const Cube& offC : offCubes)
	{
		Cube onC = cube.Intersection(offC);
		if (onC.Volume())
			newOnCubes.push_back(onC);
	}

	onCubes.insert(onCubes.end(), newOnCubes.begin(), newOnCubes.end());
	offCubes.insert(offCubes.end(), newOffCubes.begin(), newOffCubes.end());
}

long long int CubeMap::Volume() const
{
	auto Accumulate = [](const std::vector<Cube>& cubes)
	{
		return std::accumulate(
			cubes.begin(),
			cubes.end(),
			0ll,
			[](long long int vol, const Cube& c) { return vol + c.Volume(); });
	};

	return Accumulate(onCubes) - Accumulate(offCubes);
}
