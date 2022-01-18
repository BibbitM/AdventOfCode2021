#pragma once

#include <istream>
#include <string>
#include <vector>

class Heightmap
{
public:
	struct Coord
	{
		size_t row;
		size_t col;
		auto operator<=>(const Coord& right) const = default;
	};

	size_t GetRows() const { return m_heightmap.size(); }
	size_t GetColumns() const { return !m_heightmap.empty() ? m_heightmap[0].size() : 0; }
	const std::vector<char>& operator[](size_t r) const { return m_heightmap[r]; }

	std::vector<Coord> FindLowPointsCoords() const;
	std::vector<char> FindLowPoints() const;
	int CalculateSumOfRiskLevel() const;
	std::vector<int> FindBasins() const;

	bool IsValidCoord(const Coord& coord) const
	{
		return coord.row >= 0 && coord.row < GetRows() &&
			coord.col >= 0 && coord.col < GetColumns();
	}

private:
	std::vector<std::vector<char>> m_heightmap;

	friend std::istream& operator>>(std::istream& input, Heightmap& heightmap);
};

std::istream& operator>>(std::istream& input, Heightmap& heightmap);
