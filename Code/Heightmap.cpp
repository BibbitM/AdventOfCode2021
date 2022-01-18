#include "pch.h"

#include "Heightmap.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <numeric>
#include <set>
#include <vector>

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

std::vector<Heightmap::Coord> Heightmap::FindLowPointsCoords() const
{
	std::vector<Coord> lowPointsCoords{};

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
				lowPointsCoords.emplace_back(r, c);
		}
	}

	return lowPointsCoords;
}

std::vector<char> Heightmap::FindLowPoints() const
{
	std::vector<Coord> lowPointsCoords = FindLowPointsCoords();
	std::vector<char> lowPoints{};
	lowPoints.reserve(lowPointsCoords.size());

	for (const auto& coord : lowPointsCoords)
		lowPoints.push_back((*this)[coord.row][coord.col]);

	return lowPoints;
}

int Heightmap::CalculateSumOfRiskLevel() const
{
	auto lowPoints = FindLowPoints();
	return std::accumulate(lowPoints.begin(), lowPoints.end(), static_cast<int>(lowPoints.size()));
}

std::vector<int> Heightmap::FindBasins() const
{
	std::vector<int> basins;
	std::vector<Coord> lowPointsCoords = FindLowPointsCoords();

	for (const Coord& lowCoord : lowPointsCoords)
	{
		int basin = 0;
		std::set<Coord> coordsInBasin;
		std::vector<Coord> coordsToCheck({ lowCoord });
		while (!coordsToCheck.empty())
		{
			std::vector<Coord> coords;
			std::swap(coords, coordsToCheck);

			for (const Coord& coord : coords)
			{
				if (!coordsInBasin.insert(coord).second)
					continue;
				++basin;

				char height = m_heightmap[coord.row][coord.col];
				std::array<Coord, 4> neigtbours({ { coord.row - 1, coord.col }, {coord.row + 1, coord.col }, {coord.row, coord.col - 1 }, {coord.row, coord.col + 1 } });
				for (const Coord& neighbourCoord : neigtbours)
				{
					if (!IsValidCoord(neighbourCoord))
						continue;
					char neighbourHeight = m_heightmap[neighbourCoord.row][neighbourCoord.col];
					if (neighbourHeight >= 9 || neighbourHeight <= height)
						continue;
					coordsToCheck.push_back(neighbourCoord);
				}
			}
		}
		basins.push_back(basin);
	}

	std::sort(basins.begin(), basins.end(), std::greater<int>());
	return basins;
}
