#pragma once

#include "IntVector3.h"

#include <array>
#include <istream>
#include <vector>

class Scanner
{
public:
	enum Axis
	{
		X = 1,
		Y = 2,
		Z = 3
	};

	Scanner() = default;
	Scanner(std::vector<IntVector3> beacons)
		: m_beacons(std::move(beacons))
	{
		SortBeacons();
	}

	size_t BeaconsCount() const { return m_beacons.size(); }
	bool ContainsBeacon(const IntVector3& beacon) const;

	IntVector3 GetOffset() const { return m_offset; }

	void Merge(const Scanner& other);
	bool OverlapWith(const Scanner& orgin, size_t count);

	friend std::istream& operator>>(std::istream& in, Scanner& scanner);

private:
	bool OverlapWithTransformed(const Scanner& orgin, size_t count);
	bool FindOverlappingPairsWithOffset(const Scanner& orgin, size_t count, const IntVector3& offset) const;

	void SortBeacons();
	void TransformBeacons(const IntVector3& transform);

	struct LessBeacon
	{
		bool operator()(const IntVector3& a, const IntVector3& b) const
		{
			if (a.x < b.x)
				return true;
			if (a.x > b.x)
				return false;

			if (a.y < b.y)
				return true;
			if (a.y > b.y)
				return false;

			if (a.z < b.z)
				return true;

			return false;
		}
	};

	std::vector<IntVector3> m_beacons;
	IntVector3 m_offset{};

	static std::array<IntVector3, 24> s_transforms;
};
