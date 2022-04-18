#include "pch.h"
#include "Scanner.h"

#include <algorithm>
#include <array>
#include <sstream>
#include <string>

bool Scanner::ContainsBeacon(const IntVector3& beacon) const
{
	return std::find(m_beacons.begin(), m_beacons.end(), beacon) != m_beacons.end();
}

bool Scanner::MergeOld(const Scanner& other, size_t count)
{
	if (count < 1)
		return false;
	if (count > m_beacons.size() || count > other.m_beacons.size())
		return false;

	std::vector<size_t> myIndices;
	std::vector<size_t> otherIndices;
	myIndices.reserve(count);
	otherIndices.reserve(count);

	if (!FindOverlappingBeacons(other, count, myIndices, otherIndices))
		return false;

	MergeBeacons(other, myIndices, otherIndices);

	return true;
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

void Scanner::MergeBeacons(const Scanner& other, const std::vector<size_t>& myIndices, const std::vector<size_t>& otherIndices)
{
	std::array<size_t, 3> coords{};
	std::array<int, 3> signs{};
	std::array<size_t, 3> candidates{ 0, 1, 2 };

	// Find coordinates.
	size_t myC{};
	for (myC = 0; myC < 2; ++myC)
	{
		size_t c = candidates[myC];
		size_t idx{};
		for (idx = 1; idx < myIndices.size(); ++idx)
		{
			if (m_beacons[myIndices[0]][0] - m_beacons[myIndices[idx]][0] !=
				other.m_beacons[otherIndices[0]][c] - other.m_beacons[otherIndices[idx]][c])
			{
				break;
			}
		}
		if (idx == myIndices.size())
			break;
	}
	coords[0] = candidates[myC];
	candidates[myC] = candidates.back();

	{
		size_t c = candidates[0];
		size_t idx{};
		for (idx = 1; idx < myIndices.size(); ++idx)
		{
			if (m_beacons[myIndices[0]][1] - m_beacons[myIndices[idx]][1] !=
				other.m_beacons[otherIndices[0]][c] - other.m_beacons[otherIndices[idx]][c])
			{
				break;
			}
		}
		if (idx == myIndices.size())
		{
			coords[1] = candidates[0];
			coords[2] = candidates[1];
		}
		else
		{
			coords[1] = candidates[1];
			coords[2] = candidates[0];
		}
	}

	// Find sign.
	for (myC = 0; myC < 3; ++myC)
	{
		const size_t otherC = coords[myC];

		for (size_t idx = 1; idx < myIndices.size(); ++idx)
		{
			if (m_beacons[myIndices[0]][myC] - m_beacons[myIndices[idx]][myC] == 0)
				continue;
			
			signs[myC] = (m_beacons[myIndices[0]][myC] - m_beacons[myIndices[idx]][myC] ==
				other.m_beacons[otherIndices[0]][otherC] - other.m_beacons[otherIndices[idx]][otherC])
				? 1 : -1;

			break;
		}
	}

	const IntVector3 offset = {
		m_beacons[myIndices[0]][0] - other.m_beacons[otherIndices[0]][coords[0]] * signs[0],
		m_beacons[myIndices[0]][1] - other.m_beacons[otherIndices[0]][coords[1]] * signs[1],
		m_beacons[myIndices[0]][2] - other.m_beacons[otherIndices[0]][coords[2]] * signs[2]
	};

	for (const IntVector3& otherBeacon : other.m_beacons)
	{

		IntVector3 otherBeaconInMyCoords{
			otherBeacon[coords[0]] * signs[0],
			otherBeacon[coords[1]] * signs[1],
			otherBeacon[coords[2]] * signs[2]
		};
		IntVector3 otherBeaconInMySpace = otherBeaconInMyCoords + offset;
		if (!ContainsBeacon(otherBeaconInMySpace))
			m_beacons.push_back(otherBeaconInMySpace);
	}
}

bool Scanner::FindOverlappingBeacons(const Scanner& other, size_t count, std::vector<size_t>& myIndices, std::vector<size_t>& otherIndices) const
{
	const size_t firstIdx = myIndices.empty() ? 0 : myIndices.back() + 1;
	const size_t lastIdx = m_beacons.size() - count + myIndices.size() + 1;
	for (size_t idx = firstIdx; idx < lastIdx; ++idx)
	{
		myIndices.push_back(idx);
		if (myIndices.size() == count)
		{
			if (FindMatchingOverlappingBeacons(other, count, myIndices, otherIndices))
				return true;
		}
		else
		{
			if (FindOverlappingBeacons(other, count, myIndices, otherIndices))
				return true;
		}
		myIndices.pop_back();
	}
	return false;
}

bool Scanner::FindMatchingOverlappingBeacons(const Scanner& other, size_t count, const std::vector<size_t>& myIndices, std::vector<size_t>& otherIndices) const
{
	for (size_t idx = 0; idx < other.m_beacons.size(); ++idx)
	{
		// Skip if index was already used.
		if (std::find(otherIndices.begin(), otherIndices.end(), idx) != otherIndices.end())
			continue;

		otherIndices.push_back(idx);
		if (CompareOverlappingBeacons(other, otherIndices.size(), myIndices, otherIndices)) //m_beacons[myIndices[otherIndices.size() - 1]] == other.m_beacons[idx])//
		{
			if (otherIndices.size() == count)
				return true;
			else if (FindMatchingOverlappingBeacons(other, count, myIndices, otherIndices))
				return true;
		}
		otherIndices.pop_back();
	}

	return false;
}

bool Scanner::CompareOverlappingBeacons(const Scanner& other, size_t count, const std::vector<size_t>& myIndices, const std::vector<size_t>& otherIndices) const
{
	if (count <= 1)
		return true;

	const size_t last = count - 1;
	for (size_t idx = 0; idx < last; ++idx)
	{
		const int myDistance2 = Distance2(m_beacons[myIndices[last]], m_beacons[myIndices[idx]]);
		const int otherDistance2 = Distance2(other.m_beacons[otherIndices[last]], other.m_beacons[otherIndices[idx]]);
		if (myDistance2 != otherDistance2)
			return false;
	}

	return CompareOverlappingBeacons(other, count - 1, myIndices, otherIndices);
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
