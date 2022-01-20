#pragma once

#include "IntVector2.h"

#include <array>
#include <istream>
#include <string>

class OctopusGrid
{
public:
	static constexpr const int c_gridSize = 10;

	int Get(const IntVector2& pos) const { return m_energy[GetIdx(pos)]; }
	void Set(const IntVector2& pos, int energy) { m_energy[GetIdx(pos)] = energy; }
	bool IsValid(const IntVector2& pos) const
	{
		return pos.x >= 0 && pos.y >= 0 && pos.x < c_gridSize && pos.y < c_gridSize;
	}

	void Step(int steps = 1);
	int GetSteps() const { return m_steps; }
	int GetFlashes() const { return m_flashes; }
	bool AllFlashed() const { return m_allFlashed; }

private:
	void IncreaseEnergy(const IntVector2& pos);
	void Flash(const IntVector2& pos);

	size_t GetIdx(const IntVector2& pos) const
	{
		return static_cast<size_t>(pos.x + pos.y * c_gridSize);
	}
	std::array<int, c_gridSize* c_gridSize> m_energy{};
	int m_steps{};
	int m_flashes{};
	bool m_allFlashed{};
};

std::istream& operator>>(std::istream& in, OctopusGrid& grid);
