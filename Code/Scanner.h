#pragma once

#include "IntVector3.h"

#include <istream>
#include <vector>

class Scanner
{
public:
	Scanner() = default;
	Scanner(std::vector<IntVector3> beacons)
		: m_beacons(std::move(beacons))
	{
	}

	size_t BeaconsCount() const { return m_beacons.size(); }

	bool Merge(const Scanner& other, size_t count);

	friend std::istream& operator>>(std::istream& in, Scanner& scanner);

private:
	bool FindOverlappingBeacons(const Scanner& other, size_t count, std::vector<size_t>& myIndices, std::vector<size_t>& otherIndices) const;
	bool FindMatchingOverlappingBeacons(const Scanner& other, size_t count, const std::vector<size_t>& myIndices, std::vector<size_t>& otherIndices) const;
	bool CompareOverlappingBeacons(const Scanner& other, size_t count, const std::vector<size_t>& myIndices, const std::vector<size_t>& otherIndices) const;

	std::vector<IntVector3> m_beacons;
};
