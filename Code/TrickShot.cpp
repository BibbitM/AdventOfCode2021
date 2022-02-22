#include "pch.h"
#include "TrickShot.h"

std::istream& operator>>(std::istream& in, TrickShot::TargetArea& area)
{
	int minX, maxX, minY, maxY;

	in.ignore(15); //< "target area: x="
	in >> minX;
	in.ignore(2); //< ".."
	in >> maxX;
	in.ignore(4); //< ", y="
	in >> minY;
	in.ignore(2); //< ".."
	in >> maxY;

	area = TrickShot::TargetArea{ { minX, minY }, { maxX, maxY } };

	return in;
}
