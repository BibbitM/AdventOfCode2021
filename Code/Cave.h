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
			: name(name), neighbors(), isStart(isStart), isEnd(isEnd), isSmall(isSmall)
		{}

		std::string name;
		std::vector<Cave*> neighbors;
		bool isStart = false;
		bool isEnd = false;
		bool isSmall = false;
	};

	class Path
	{
	public:
		explicit Path(const Cave* startCave)
			: last(startCave)
		{
			AddLastToBlocked();
		}
		Path(const Path& prevPath, const Cave* neighbor)
			: Path(prevPath)
		{
			last = neighbor;
			AddLastToBlocked();
		}
		void AddLastToBlocked()
		{
			if (last->isSmall)
			{
				auto it = std::find(blocked.begin(), blocked.end(), last);
				if (it != blocked.end())
					doubleVisit = true;
				else
					blocked.push_back(last);
			}
		}
		bool IsBlocked(const Cave* cave, bool allowSingleSmallCaveDoubleVisit) const
		{
			auto it = std::find(blocked.begin(), blocked.end(), cave);
			if (it == blocked.end())
				return false;

			if (!allowSingleSmallCaveDoubleVisit)
				return true;
			else
				return doubleVisit;
		}

		const Cave* last = nullptr;
		std::vector<const Cave*> blocked;
		bool doubleVisit = false;
	};

	Cave* FindOrCreateCave(std::string_view name);
	Cave* FindCave(std::string_view name) const;

	std::vector<std::unique_ptr<Cave>> m_caves;
};

std::istream& operator>>(std::istream& in, CavesMap& map);
