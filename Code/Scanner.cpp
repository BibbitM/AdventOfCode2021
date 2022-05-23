#include "pch.h"
#include "Scanner.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <sstream>
#include <string>

std::array<IntVector3, 24> Scanner::s_transforms = {
	IntVector3{ X, Y, Z }, IntVector3{ Y, Z, X }, IntVector3{ Z, X, Y }, IntVector3{ -X, Z, Y },
	IntVector3{ Z, Y, -X }, IntVector3{ Y, -X, Z }, IntVector3{ X, Z, -Y }, IntVector3{ Z, -Y, X },
	IntVector3{ -Y, X, Z }, IntVector3{ X, -Z, Y }, IntVector3{ -Z, Y, X }, IntVector3{ Y, X, -Z },
	IntVector3{ -X, -Y, Z }, IntVector3{ -Y, Z, -X }, IntVector3{ Z, -X, -Y }, IntVector3{ -X, Y, -Z },
	IntVector3{ Y, -Z, -X }, IntVector3{ -Z, -X, Y }, IntVector3{ X, -Y, -Z }, IntVector3{ -Y, -Z, X },
	IntVector3{ -Z, X, -Y }, IntVector3{ -X, -Z, -Y }, IntVector3{ -Z, -Y, -X }, IntVector3{ -Y, -X, -Z }
};

bool Scanner::ContainsBeacon(const IntVector3& beacon) const
{
	return std::binary_search(m_beacons.begin(), m_beacons.end(), beacon, LessBeacon{});
}

void Scanner::Merge(const Scanner& other)
{
	std::vector<IntVector3> beaconsToAdd;
	beaconsToAdd.reserve(other.m_beacons.size());
	for (size_t i = 0; i < other.m_beacons.size(); ++i)
	{
		IntVector3 otherBeaconInMyCoords = other.m_beacons[i] + other.m_offset - m_offset;
		if (!ContainsBeacon(otherBeaconInMyCoords))
			beaconsToAdd.push_back(otherBeaconInMyCoords);
	}

	if (!beaconsToAdd.empty())
	{
		m_beacons.insert(m_beacons.end(), beaconsToAdd.begin(), beaconsToAdd.end());
		SortBeacons();
	}
}

bool Scanner::OverlapWith(const Scanner& orgin, size_t count)
{
	Scanner transformed;
	for (size_t i = 0; i < s_transforms.size(); ++i)
	{
		transformed = *this;
		transformed.TransformBeacons(s_transforms[i]);

		if (transformed.OverlapWithTransformed(orgin, count))
		{
			*this = transformed;
			return true;
		}
	}

	return false;
}

bool Scanner::OverlapWithTransformed(const Scanner& orgin, size_t count)
{
	for (size_t myIdx = 0; myIdx < m_beacons.size(); ++myIdx)
	{
		for (size_t orgIdx = 0; orgIdx < orgin.m_beacons.size(); ++orgIdx)
		{
			IntVector3 offset = orgin.m_beacons[orgIdx] - m_beacons[myIdx];
			if (FindOverlappingPairsWithOffset(orgin, count, offset))
			{
				m_offset = orgin.m_offset + offset;
				return true;
			}
		}
	}
	return false;
}

bool Scanner::FindOverlappingPairsWithOffset(const Scanner& orgin, size_t count, const IntVector3& offset) const
{
	LessBeacon compare{};
	size_t i = 0;
	size_t j = 0;
	int overlappingCount = 0;

	while (i < m_beacons.size() && j < orgin.m_beacons.size())
	{
		const size_t maxIncrement = std::max(m_beacons.size() - i, orgin.m_beacons.size() - j);
		if (overlappingCount + maxIncrement < count)
		{
			break;
		}

		if (compare(m_beacons[i] + offset, orgin.m_beacons[j]))
			++i;
		else if (compare(orgin.m_beacons[j], m_beacons[i] + offset))
			++j;
		else
		{
			++overlappingCount;
			++i;
			++j;
		}
	}

	return overlappingCount >= count;
}

void Scanner::SortBeacons()
{
	std::sort(m_beacons.begin(), m_beacons.end(), LessBeacon{});
}

void Scanner::TransformBeacons(const IntVector3& transform)
{
	auto coord = [](const IntVector3& beacon, int xyz) { return beacon[std::abs(xyz) - 1] * (xyz >= 0 ? 1 : -1); };

	for (auto& beacon : m_beacons)
	{
		beacon = IntVector3{ coord(beacon, transform.x), coord(beacon, transform.y), coord(beacon, transform.z) };
	}

	SortBeacons();
}

std::istream& operator>>(std::istream& in, Scanner& scanner)
{
	std::string line;
	std::getline(in, line); //< Skip header "--- scanner 0 ---".
	while (std::getline(in, line) && !line.empty())
	{
		std::istringstream inLine(line);
		inLine >> scanner.m_beacons.emplace_back();
	}
	scanner.SortBeacons();

	return in;
}
