#pragma once

#include "IntVector2.h"

#include <iostream>
#include <vector>

namespace TrickShot
{
	class TargetArea
	{
	public:
		TargetArea() = default;
		TargetArea(const IntVector2& minPoint, const IntVector2& maxPoint)
			: m_min(minPoint)
			, m_max(maxPoint)
		{ }

		const IntVector2& GetMin() const { return m_min; }
		const IntVector2& GetMax() const { return m_max; }

	private:
		IntVector2 m_min{};
		IntVector2 m_max{};
	};

	std::vector<int> GetXForces(const TargetArea& area);
	std::vector<int> GetYForces(const TargetArea& area);

	bool SimuleteShot(const IntVector2& shot, const TargetArea& area);

	std::vector<IntVector2> FindAllShots(const TargetArea& area);
	IntVector2 FindHighestShot(const TargetArea& area);

	int GetHighestPosition(int shotY);
}

std::istream& operator>>(std::istream& in, TrickShot::TargetArea& area);
