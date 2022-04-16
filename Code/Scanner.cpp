#include "pch.h"
#include "Scanner.h"

#include <algorithm>
#include <sstream>
#include <string>

bool Scanner::ContainsBeacon(const IntVector3& beacon) const
{
	return std::find(m_beacons.begin(), m_beacons.end(), beacon) != m_beacons.end();
}

bool Scanner::Merge(const Scanner& other, size_t count)
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

void Scanner::MergeBeacons(const Scanner& other, const std::vector<size_t>& myIndices, const std::vector<size_t>& otherIndices)
{
	const IntVector3 offset = m_beacons[myIndices[0]] - other.m_beacons[otherIndices[0]];

	for (const IntVector3& otherBeacon : other.m_beacons)
	{
		IntVector3 otherBeaconInMySpace = otherBeacon + offset;
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
