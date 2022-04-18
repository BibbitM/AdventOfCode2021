#include "pch.h"
#include "Scanner.h"

#include <algorithm>
#include <array>
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
	return std::find(m_beacons.begin(), m_beacons.end(), beacon) != m_beacons.end();
}

void Scanner::Merge(const Scanner& other)
{
	for (size_t i = 0; i < other.m_beacons.size(); ++i)
	{
		IntVector3 otherBeaconInMyCoords = other.m_beacons[i] + other.m_offset - m_offset;
		if (!ContainsBeacon(otherBeaconInMyCoords))
			m_beacons.push_back(otherBeaconInMyCoords);
	}

	SortBeacons();
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
	int overlappingCount = 0;
	for (size_t i = 0; i < m_beacons.size(); ++i)
	{
		if (orgin.ContainsBeacon(m_beacons[i] + offset))
		{
			++overlappingCount;
		}
	}

	return overlappingCount >= count;
}

void Scanner::SortBeacons()
{
	std::sort(m_beacons.begin(), m_beacons.end(), [](const IntVector3& a, const IntVector3& b)
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
	});
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

	return in;
}
