#pragma once

#include <istream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

class CavesMap
{
public:
	void AddConnection(std::string_view first, std::string_view second);
	int FindDistinctPathsCount(bool allowSingleSmallCaveDoubleVisit = false) const;

private:
	class Cave
	{
	public:
		Cave(std::string_view name, bool isStart, bool isEnd, bool isSmall)
			: name(name), neighborIdxes(), isStart(isStart), isEnd(isEnd), isSmall(isSmall)
		{}

		std::string name;
		std::vector<size_t> neighborIdxes;
		bool isStart = false;
		bool isEnd = false;
		bool isSmall = false;
	};

	class Path
	{
	public:
		explicit Path(const CavesMap& owner, size_t startCaveIdx)
			: lastIdx(startCaveIdx)
		{
			AddLastToBlocked(owner);
		}
		Path(const CavesMap& owner, const Path& prevPath, size_t neighborIdx)
			: Path(prevPath)
		{
			lastIdx = neighborIdx;
			AddLastToBlocked(owner);
		}
		void AddLastToBlocked(const CavesMap& owner)
		{
			const Cave* last = owner.m_caves[lastIdx].get();
			if (last->isSmall)
			{
				const size_t lastMask = 1ull << lastIdx;
				if ((blocked & lastMask) == 0)
					blocked |= lastMask;
				else
					doubleVisit = true;
			}
		}
		bool IsBlocked(size_t caveIdx, bool allowSingleSmallCaveDoubleVisit) const
		{
			const size_t caveMask = 1ull << caveIdx;
			if ((blocked & caveMask) == 0)
				return false;

			if (!allowSingleSmallCaveDoubleVisit)
				return true;
			else
				return doubleVisit;
		}

		size_t lastIdx = 0;
		uint64_t blocked = 0;
		bool doubleVisit = false;
	};

	Cave* FindOrCreateCave(std::string_view name);
	Cave* FindCave(std::string_view name) const;
	size_t GetCaveIdx(const Cave* cave) const;

	std::vector<std::unique_ptr<Cave>> m_caves;
};

std::istream& operator>>(std::istream& in, CavesMap& map);
