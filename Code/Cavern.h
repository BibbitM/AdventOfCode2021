#pragma once

#include <cassert>
#include <istream>
#include <vector>

class Cavern
{
public:
	int GetSizeX() const { return m_sizeX; }
	int GetSizeY() const { return m_sizeY; }
	int Get(int x, int y) const { return m_cells[GetCellIndex(x, y)]; }

	int CalculateRisk() const;

private:
	int CalculateHeuristicScore(size_t idx) const;
	std::vector<size_t> GetNeigborIndices(size_t idx) const;
	inline size_t GetCellIndex(int x, int y) const
	{
		assert(x >= 0 && x < m_sizeX);
		assert(y >= 0 && y < m_sizeY);
		return static_cast<size_t>(x + y * m_sizeX);
	}
	void Resize(int x, int y);

	std::vector<int> m_cells;
	int m_sizeX = 0;
	int m_sizeY = 0;

	friend std::istream& operator>>(std::istream& in, Cavern& cavern);
};

std::istream& operator>>(std::istream& in, Cavern& cavern);
