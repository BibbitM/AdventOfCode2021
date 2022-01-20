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
			: path({ startCave })
		{
			if (startCave->isSmall)
				blocked.push_back(startCave);
		}
		Path(const Path& prevPath, const Cave* neighbor)
			: Path(prevPath)
		{
			path.push_back(neighbor);
			if (neighbor->isSmall)
				blocked.push_back(neighbor);
		}
		std::vector<const Cave*> path;
		std::vector<const Cave*> blocked;
	};

	Cave* FindOrCreateCave(std::string_view name);
	Cave* FindCave(std::string_view name) const;

	std::vector<std::unique_ptr<Cave>> m_caves;
};

std::istream& operator>>(std::istream& in, CavesMap& map);
