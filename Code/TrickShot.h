#pragma once

#include "IntVector2.h"

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
}
