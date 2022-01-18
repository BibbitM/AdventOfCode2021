#pragma once

#include <istream>
#include <string>
#include <vector>

class Heightmap
{
public:
	size_t GetRows() const { return m_heightmap.size(); }
	size_t GetColumns() const { return !m_heightmap.empty() ? m_heightmap[0].size() : 0; }
	const std::vector<char>& operator[](size_t x) const { return m_heightmap[x]; }

	std::vector<char> FindLowPoints() const;
	int CalculateSumOfRiskLevel() const;

private:
	std::vector<std::vector<char>> m_heightmap;

	friend std::istream& operator>>(std::istream& input, Heightmap& heightmap);
};

std::istream& operator>>(std::istream& input, Heightmap& heightmap);
