#include "pch.h"

#include "Cavern.h"

#include <algorithm>
#include <string>

inline int Cavern::CalculateHeuristicScore(size_t idx) const
{
	const int x = static_cast<int>(idx % static_cast<size_t>(m_sizeX));
	const int y = static_cast<int>(idx / static_cast<size_t>(m_sizeX));
	return (m_sizeX - 1 - x) + (m_sizeY - 1 - y);
}

inline std::vector<size_t> Cavern::GetNeigborIndices(size_t idx) const
{
	std::vector<size_t> neighborIndices;
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

	return neighborIndices;
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

	while (!openCells.empty())
	{
		std::sort(openCells.begin(), openCells.end(), [this, &globalScore = std::as_const(globalScore)](size_t left, size_t right)
		{
			return globalScore[left] + CalculateHeuristicScore(left) > globalScore[right] + CalculateHeuristicScore(right);
		});

		const size_t currentIdx = openCells.back();
		openCells.pop_back();
		closedCells[currentIdx] = true;

		if (currentIdx == endIdx)
			return globalScore[currentIdx];

		for (size_t neigborIdx : GetNeigborIndices(currentIdx))
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
