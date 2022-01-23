#include "pch.h"

#include "Cavern.h"

#include <string>

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
