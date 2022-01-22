#include "pch.h"

#include "Polymerization.h"

#include <unordered_map>
#include <utility>
#include <limits>

void Polimer::Grow(const std::vector<std::pair<std::string, char>>& instructions)
{
	if (m_polimer.length() < 2)
		return;

	std::string newPolimer;
	newPolimer.reserve(m_polimer.length() * 2 - 1);

	for (size_t i = 0; i + 1 < m_polimer.length(); ++i)
	{
		newPolimer.push_back(m_polimer[i]);
		for (const auto& inst : instructions)
		{
			if (m_polimer[i] == inst.first[0] && m_polimer[i + 1] == inst.first[1])
			{
				newPolimer.push_back(inst.second);
				break;
			}
		}
	}
	newPolimer.push_back(m_polimer.back());

	std::swap(m_polimer, newPolimer);
}

int Polimer::CalculteMostSubLessQuantity() const
{
	std::unordered_map<char, int> quanties;
	for (char elem : m_polimer)
		++quanties[elem];

	int maxCount = std::numeric_limits<int>::min();
	int minCount = std::numeric_limits<int>::max();

	for (auto it : quanties)
	{
		maxCount = std::max(it.second, maxCount);
		minCount = std::min(it.second, minCount);
	}

	return maxCount - minCount;
}

std::istream& operator>>(std::istream& in, Polimer& polimer)
{
	std::getline(in, polimer.m_polimer);
	return in;
}

std::istream& operator>>(std::istream& in, std::vector<std::pair<std::string, char>>& instructions)
{
	std::string line;
	while (std::getline(in, line))
	{
		if (line.size() < 7)
			continue;
		instructions.emplace_back(line.substr(0, 2), line[6]);
	}
	return in;
}
