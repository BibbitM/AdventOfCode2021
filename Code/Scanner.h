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

	friend std::istream& operator>>(std::istream& in, Scanner& scanner);

private:
	std::vector<IntVector3> m_beacons;
};
