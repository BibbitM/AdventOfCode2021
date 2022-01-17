#include "pch.h"

#include "Heightmap.h"

#include <cassert>

std::istream& operator>>(std::istream& input, Heightmap& heightmap)
{
	std::string line;
	while (std::getline(input, line))
	{
		std::vector<char>& row = heightmap.m_heightmap.emplace_back();
		row.reserve(line.length());
		for (char c : line)
		{
			row.push_back(c - '0');
		}
		assert(row.size() == heightmap.GetColumns());
	}
	return input;
}

std::vector<char> Heightmap::GetLowPoints() const
{
	std::vector<char> lowPoints{};

	for (size_t r = 0; r < GetRows(); ++r)
	{
		for (size_t c = 0; c < GetColumns(); ++c)
		{
			const char point = m_heightmap[r][c];
			bool isLowPoint = true;

			if (r > 0 && m_heightmap[r - 1][c] <= point)
				isLowPoint = false;
			if (r + 1 < GetRows() && m_heightmap[r + 1][c] <= point)
				isLowPoint = false;
			if (c > 0 && m_heightmap[r][c - 1] <= point)
				isLowPoint = false;
			if (c + 1 < GetColumns() && m_heightmap[r][c + 1] <= point)
				isLowPoint = false;

			if (isLowPoint)
				lowPoints.push_back(point);
		}
	}

	return lowPoints;
}
