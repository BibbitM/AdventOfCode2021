#include "pch.h"

#include "IntLine2.h"

#include <istream>
#include <unordered_map>
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

int CountDangerousPoints(const std::vector<IntLine2>& lines)
{
	std::unordered_map<IntVector2, int> occupiedPoints;

	for (const IntLine2& line : lines)
	{
		if (line.first.x == line.second.x)
		{
			for (int y = std::min(line.first.y, line.second.y), yEnd = std::max(line.first.y, line.second.y) + 1; y != yEnd; ++y)
				++occupiedPoints[IntVector2(line.first.x, y)];
		}
		else if (line.first.y == line.second.y)
		{
			for (int x = std::min(line.first.x, line.second.x), xEnd = std::max(line.first.x, line.second.x) + 1; x != xEnd; ++x)
				++occupiedPoints[IntVector2(x, line.first.y)];
		}
	}

	int dangerousPoints = 0;
	for (auto point : occupiedPoints)
	{
		if (point.second > 1)
			++dangerousPoints;
	}
	return dangerousPoints;
}

int CountDangerousPointsWithDiagonal(const std::vector<IntLine2>& lines)
{
	std::unordered_map<IntVector2, int> occupiedPoints;

	for (const IntLine2& line : lines)
	{
		if (line.first.x == line.second.x ||
			line.first.y == line.second.y ||
			std::abs(line.first.x - line.second.x) == std::abs(line.first.y - line.second.y))
		{
			int xStep = line.first.x != line.second.x ? (line.first.x < line.second.x ? 1 : -1) : 0;
			int yStep = line.first.y != line.second.y ? (line.first.y < line.second.y ? 1 : -1) : 0;
			for (int x = line.first.x, y = line.first.y;
					x != line.second.x + xStep || y != line.second.y + yStep;
					x += xStep, y += yStep)
				++occupiedPoints[IntVector2(x, y)];
		}
	}

	int dangerousPoints = 0;
	for (auto point : occupiedPoints)
	{
		if (point.second > 1)
			++dangerousPoints;
	}
	return dangerousPoints;
}
