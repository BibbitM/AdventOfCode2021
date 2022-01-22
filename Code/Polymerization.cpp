#include "pch.h"

#include "Polymerization.h"

#include <utility>
#include <limits>

void Polimer::SetPolimer(std::string_view polimer)
{
	m_pairs.clear();
	m_chars.clear();

	if (polimer.empty())
		return;

	for (size_t i = 0; i + 1 < polimer.length(); ++i)
	{
		++m_pairs[{ polimer[i], polimer[i + 1] }];
		++m_chars[polimer[i]];
	}
	++m_chars[polimer.back()];
}

void Polimer::Grow(const std::vector<std::pair<PolimerPair, char>>& instructions)
{
	std::unordered_map<PolimerPair, size_t> newPairs;
	newPairs.reserve(m_pairs.size() * 2);

	for (const auto& pair : m_pairs)
	{
		for (const auto& inst : instructions)
		{
			if (pair.first == inst.first)
			{
				newPairs[{ pair.first.chars[0], inst.second }] += pair.second;
				newPairs[{ inst.second, pair.first.chars[1] }] += pair.second;
				m_chars[inst.second] += pair.second;
			}
		}

	}

	std::swap(m_pairs, newPairs);
}

size_t Polimer::CalculteMostSubLessQuantity() const
{
	size_t maxCount = std::numeric_limits<size_t>::min();
	size_t minCount = std::numeric_limits<size_t>::max();

	for (auto it : m_chars)
	{
		maxCount = std::max(it.second, maxCount);
		minCount = std::min(it.second, minCount);
	}

	return maxCount - minCount;
}

size_t Polimer::GetLength() const
{
	size_t length = 0;

	for (auto it : m_chars)
		length += it.second;

	return length;
}

std::istream& operator>>(std::istream& in, Polimer& polimer)
{
	std::string line;
	std::getline(in, line);
	polimer.SetPolimer(line);
	return in;
}

std::istream& operator>>(std::istream& in, std::vector<std::pair<PolimerPair, char>>& instructions)
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
