#include "pch.h"
#include "Cube.h"

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
