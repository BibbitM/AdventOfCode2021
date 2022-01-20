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
	int FindDistinctPathsCount() const;

private:
	class Cave
	{
	public:
		Cave(std::string_view name, bool isStart, bool isEnd, bool isSmall)
			: name(name), neightors(), isStart(isStart), isEnd(isEnd), isSmall(isSmall)
		{}

		std::string name;
		std::vector<Cave*> neightors;
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
			if (last->isSmall)
				blocked.push_back(last);
		}
		Path(const Path& prevPath, const Cave* neighbor)
			: last(neighbor), blocked(prevPath.blocked)
		{
			if (last->isSmall)
				blocked.push_back(last);
		}
		const Cave* last;
		std::vector<const Cave*> blocked;
	};

	Cave* FindOrCreateCave(std::string_view name);
	Cave* FindCave(std::string_view name) const;

	std::vector<std::unique_ptr<Cave>> m_caves;
};

std::istream& operator>>(std::istream& in, CavesMap& map);
