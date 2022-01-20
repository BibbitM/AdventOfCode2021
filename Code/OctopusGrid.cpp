#include "pch.h"
#include "OctopusGrid.h"

void OctopusGrid::Step(int steps)
{
	for (int _ = 0; _ < steps; ++_)
	{
		for (int y = 0; y < c_gridSize; ++y)
		{
			for (int x = 0; x < c_gridSize; ++x)
			{
				IncreaseEnergy({ x, y });
			}
		}

		for (int& e : m_energy)
		{
			if (e > 9)
				e = 0;
		}
	}
}

void OctopusGrid::IncreaseEnergy(const IntVector2& pos)
{
	int& e = m_energy[GetIdx(pos)];
	++e;
	if (e == 10)
		Flash(pos);;
}

void OctopusGrid::Flash(const IntVector2& explosionPosition)
{
	++m_flashes;
	for (int y = std::max(explosionPosition.y - 1, 0); y < std::min(explosionPosition.y + 2, c_gridSize); ++y)
	{
		for (int x = std::max(explosionPosition.x - 1, 0); x < std::min(explosionPosition.x + 2, c_gridSize); ++x)
		{
			IntVector2 pos{ x, y };
			if (pos != explosionPosition)
			{
				IncreaseEnergy(pos);
			}
		}
	}
}

std::istream& operator>>(std::istream& in, OctopusGrid& grid)
{
	std::string line;
	for (int y = 0; y < OctopusGrid::c_gridSize; ++y)
	{
		if (!std::getline(in, line))
			break;
		for (int x = 0; x < std::min(OctopusGrid::c_gridSize, static_cast<int>(line.length())); ++x)
			grid.Set({ x, y }, line[x] - '0');
	}
	return in;
}
