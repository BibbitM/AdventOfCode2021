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

	bool MergeOld(const Scanner& other, size_t count);

	void Merge(const Scanner& other);
	bool OverlapWith(const Scanner& orgin, size_t count);

	friend std::istream& operator>>(std::istream& in, Scanner& scanner);

private:
	bool OverlapWithTransformed(const Scanner& orgin, size_t count);
	void MergeBeacons(const Scanner& other, const std::vector<size_t>& myIndices, const std::vector<size_t>& otherIndices);

	bool FindOverlappingBeacons(const Scanner& other, size_t count, std::vector<size_t>& myIndices, std::vector<size_t>& otherIndices) const;
	bool FindMatchingOverlappingBeacons(const Scanner& other, size_t count, const std::vector<size_t>& myIndices, std::vector<size_t>& otherIndices) const;
	bool CompareOverlappingBeacons(const Scanner& other, size_t count, const std::vector<size_t>& myIndices, const std::vector<size_t>& otherIndices) const;

	bool FindOverlappingPairsWithOffset(const Scanner& orgin, size_t count, const IntVector3& offset) const;

	void SortBeacons();
	void TransformBeacons(const IntVector3& transform);

	std::vector<IntVector3> m_beacons;
	IntVector3 m_offset{};

	static std::array<IntVector3, 24> s_transforms;
};
