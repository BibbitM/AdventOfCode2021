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

void CubeMap::OnOff(const Cube& cube, bool addNewCube)
{
	std::vector<Cube> newOnCubes;
	std::vector<Cube> newOffCubes;

	for (auto onIt = onCubes.begin(); onIt != onCubes.end(); /* inside loop */)
	{
		Cube& onC = *onIt;
		Cube offC = cube.Intersection(onC);
		if (offC.Volume())
		{
			if (offC == onC)
			{
				// The off cube is the same as the on cube.
				// Remove the current cube by replacing it with the back.
				auto onOffset = std::distance(onCubes.begin(), onIt);
				onC = onCubes.back();
				onCubes.pop_back();
				onIt = onCubes.begin() + onOffset; //< To suppress DEBUG iterator check. Changed vector size during iterating.
				continue;
			}
			if (addNewCube && offC == cube)
				addNewCube = false;
			else
				newOffCubes.push_back(offC);
		}
		++onIt;
	}

	for (auto offIt = offCubes.begin(); offIt != offCubes.end(); /* inside loop */)
	{
		Cube& offC = *offIt;
		Cube onC = cube.Intersection(offC);
		if (onC.Volume())
		{
			if (onC == offC)
			{
				// The off cube is the same as the on cube.
				// Remove the current cube by replacing it with the back.
				auto offOffset = std::distance(offCubes.begin(), offIt);
				offC = offCubes.back();
				offCubes.pop_back();
				offIt = offCubes.begin() + offOffset; //< To suppress DEBUG iterator check. Changed vector size during iterating.
				continue;
			}
			else
				newOnCubes.push_back(onC);
		}
		++offIt;
	}

	// The exact reserve works worse than the default grows policy for vector. With this, we get 50% worse performance.
	//onCubes.reserve(onCubes.size() + newOnCubes.size() + static_cast<size_t>(addNewCube));
	if (addNewCube)
		onCubes.insert(onCubes.end(), cube);
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
