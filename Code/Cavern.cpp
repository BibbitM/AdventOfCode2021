#include "pch.h"

#include "Cavern.h"

#include <algorithm>
#include <limits>
#include <string>

inline int Cavern::CalculateHeuristicScore(size_t idx) const
{
	const int x = static_cast<int>(idx % static_cast<size_t>(m_sizeX));
	const int y = static_cast<int>(idx / static_cast<size_t>(m_sizeX));
	const int distX = m_sizeX - 1 - x;
	const int distY = m_sizeY - 1 - y;
	return distX + distY;
}

inline void Cavern::GetNeigborIndices(size_t idx, std::vector<size_t>& neighborIndices) const
{
	neighborIndices.clear();
	neighborIndices.reserve(4);

	const int x = static_cast<int>(idx % static_cast<size_t>(m_sizeX));
	const int y = static_cast<int>(idx / static_cast<size_t>(m_sizeX));

	if (x > 0)
		neighborIndices.push_back(GetCellIndex(x - 1, y));
	if (y > 0)
		neighborIndices.push_back(GetCellIndex(x, y - 1));
	if (x + 1 < m_sizeX)
		neighborIndices.push_back(GetCellIndex(x + 1, y));
	if (y + 1 < m_sizeY)
		neighborIndices.push_back(GetCellIndex(x, y + 1));
}

int Cavern::CalculateRisk() const
{
	assert(m_sizeX > 0 && m_sizeY > 0);

	const size_t totalCells = m_sizeX * m_sizeY;
	const size_t startIdx = 0;
	const size_t endIdx = GetCellIndex(m_sizeX - 1, m_sizeY - 1);

	std::vector<bool> closedCells(totalCells, false);
	std::vector<size_t> openCells({ startIdx });
	std::vector<int> globalScore(totalCells, 0);
	std::vector<int> heuristicScore(totalCells, 0);
	for (size_t idx = 0; idx < totalCells; ++idx)
		heuristicScore[idx] = CalculateHeuristicScore(idx);
	std::vector<size_t> neighborIndices;
	neighborIndices.reserve(4);

	while (!openCells.empty())
	{
		size_t bestOpenIdx = 0;
		int bestOpenScore = std::numeric_limits<int>::max();
		for (size_t openIdx = 0; openIdx < openCells.size(); ++openIdx)
		{
			const int openScore = globalScore[openCells[openIdx]] + heuristicScore[openCells[openIdx]];
			if (openScore < bestOpenScore)
			{
				bestOpenScore = openScore;
				bestOpenIdx = openIdx;
			}
		}

		const size_t currentIdx = openCells[bestOpenIdx];
		openCells[bestOpenIdx] = openCells.back();
		openCells.pop_back();
		closedCells[currentIdx] = true;

		if (currentIdx == endIdx)
			return globalScore[currentIdx];

		GetNeigborIndices(currentIdx, neighborIndices);
		for (size_t neigborIdx : neighborIndices)
		{
			if (closedCells[neigborIdx])
				continue;

			const int neighborGlobalScore = globalScore[currentIdx] + m_cells[neigborIdx];
			if (std::find(openCells.begin(), openCells.end(), neigborIdx) == openCells.end())
			{
				openCells.push_back(neigborIdx);
				globalScore[neigborIdx] = neighborGlobalScore;
			}
			else
			{
				globalScore[neigborIdx] = std::min(neighborGlobalScore, globalScore[neigborIdx]);
			}
		}
	}

	assert(false && "Failure. Path not found!");
	return Get(m_sizeX - 1, m_sizeY - 1);
}

void Cavern::Enlarge5x5()
{
	std::vector<int> enlargedeCells;
	enlargedeCells.resize(m_sizeX * 5 * m_sizeY * 5);

	// Copy original values.
	for (int x = 0; x < m_sizeX; ++x)
	{
		for (int y = 0; y < m_sizeY; ++y)
		{
			enlargedeCells[GetEnlarded5x5CellIndex(x, y)] = m_cells[GetCellIndex(x, y)];
		}
	}

	// Copy right.
	for (int x = m_sizeX; x < m_sizeX * 5; ++x)
	{
		for (int y = 0; y < m_sizeY; ++y)
		{
			const int prevValue = enlargedeCells[GetEnlarded5x5CellIndex(x - m_sizeX, y)];
			enlargedeCells[GetEnlarded5x5CellIndex(x, y)] = prevValue >= 9 ? 1 : prevValue + 1;
		}
	}

	// Copy down.
	for (int x = 0; x < m_sizeX * 5; ++x)
	{
		for (int y = m_sizeY; y < m_sizeY * 5; ++y)
		{
			const int prevValue = enlargedeCells[GetEnlarded5x5CellIndex(x, y - m_sizeY)];
			enlargedeCells[GetEnlarded5x5CellIndex(x, y)] = prevValue >= 9 ? 1 : prevValue + 1;
		}
	}

	std::swap(m_cells, enlargedeCells);
	m_sizeX *= 5;
	m_sizeY *= 5;
}

void Cavern::Resize(int x, int y)
{
	assert(x > 0);
	assert(y > 0);
	assert(x == m_sizeX || !m_sizeX);

	m_sizeX = x;
	m_sizeY = y;

	m_cells.resize(m_sizeX * m_sizeY);
}

std::istream& operator>>(std::istream& in, Cavern& cavern)
{
	std::string line;
	while (std::getline(in, line))
	{
		cavern.Resize(static_cast<int>(line.length()), cavern.m_sizeY + 1);
		for (int i = 0; i < line.length(); ++i)
			cavern.m_cells[cavern.GetCellIndex(i, cavern.m_sizeY - 1)] = line[i] - '0';
	}

	return in;
}
