#include "pch.h"
#include "Cave.h"

#include <cassert>
#include <cctype>

namespace
{
	constexpr const char c_startName[] = "start";
	constexpr const char c_endName[] = "end";
	constexpr const char c_separator = '-';
}

void CavesMap::AddConnection(std::string_view first, std::string_view second)
{
	Cave* firstCave = FindOrCreateCave(first);
	Cave* secondCave = FindOrCreateCave(second);
	if (!firstCave || !secondCave)
		return;
	if (firstCave == secondCave)
		return;

	firstCave->neighborIdxes.push_back(GetCaveIdx(secondCave));
	secondCave->neighborIdxes.push_back(GetCaveIdx(firstCave));
}

int CavesMap::FindDistinctPathsCount(bool allowSingleSmallCaveDoubleVisit) const
{
	const Cave* startCave = FindCave(c_startName);
	if (!startCave)
		return 0;

	std::vector<Path> pathsToCheck;
	std::vector<Path> pathsToEnd;

	pathsToCheck.emplace_back(*this, GetCaveIdx(startCave));

	while (!pathsToCheck.empty())
	{
		Path path = std::move(pathsToCheck.back());
		pathsToCheck.pop_back();

		if (m_caves[path.lastIdx]->isEnd)
		{
			pathsToEnd.push_back(std::move(path));
			continue;
		}

		for (size_t nIdx : m_caves[path.lastIdx]->neighborIdxes)
		{
			const Cave* n = m_caves[nIdx].get();

			// Skip start
			if (n->isStart)
				continue;

			// Skip blocked paths.
			if (path.IsBlocked(nIdx, allowSingleSmallCaveDoubleVisit))
				continue;

			// Create new path through neighbor n.
			pathsToCheck.emplace_back(*this, path, nIdx);
		}
	}

	return static_cast<int>(pathsToEnd.size());
}

CavesMap::Cave* CavesMap::FindOrCreateCave(std::string_view name)
{
	if (name.empty())
		return nullptr;

	if (Cave* cave = FindCave(name))
		return cave;

	m_caves.push_back(std::make_unique<Cave>(name, name == c_startName, name == c_endName, std::islower(name[0])));
	assert(m_caves.size() <= sizeof(Path::blocked) * 8);
	return m_caves.back().get();
}

CavesMap::Cave* CavesMap::FindCave(std::string_view name) const
{
	auto itFound = std::find_if(m_caves.begin(), m_caves.end(), [name](const auto& cavePtr) { return cavePtr->name == name; });
	if (itFound != m_caves.end())
		return itFound->get();

	return nullptr;
}

size_t CavesMap::GetCaveIdx(const Cave* cave) const
{
	for (size_t idx = 0; idx < m_caves.size(); ++idx)
	{
		if (m_caves[idx].get() == cave)
			return idx;
	}
	return std::numeric_limits<size_t>::max();
}

std::istream& operator>>(std::istream& in, CavesMap& map)
{
	std::string line;
	while (std::getline(in, line))
	{
		auto separator = line.find(c_separator);
		if (separator != std::string::npos)
			map.AddConnection(std::string_view(line.begin(), line.begin() + separator), std::string_view(line.begin() + separator + 1, line.end()));
	}
	return in;
}
