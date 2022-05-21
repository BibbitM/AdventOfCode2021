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
