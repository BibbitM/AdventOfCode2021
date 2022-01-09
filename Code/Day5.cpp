#include "pch.h"

#include "IntLine2.h"

#include <istream>
#include <vector>

std::vector<IntLine2> LoadLinesStream(std::istream& in)
{
	std::vector<IntLine2> lines;
	IntLine2 l;
	while (in >> l)
	{
		lines.push_back(l);
	}
	return lines;
}
