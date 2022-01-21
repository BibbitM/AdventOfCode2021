#include "pch.h"
#include "DotsPaper.h"

#include <algorithm>
#include <sstream>
#include <string>

void DotsPaper::AddDot(int x, int y)
{
	IntVector2 dot(x, y);
	if (std::find(m_dots.begin(), m_dots.end(), dot) != m_dots.end())
		return;
	m_dots.emplace_back(dot);
}

void DotsPaper::FoldAlongY(int y)
{
	auto it = std::partition(m_dots.begin(), m_dots.end(), [y](const auto& dot) { return dot.y < y; });

	std::vector<IntVector2> dotsToMirror(it, m_dots.end());
	m_dots.erase(it, m_dots.end());

	for (auto&& dot : dotsToMirror)
	{
		if (dot.y > y)
			AddDot(dot.x, 2 * y - dot.y);
	}
}

void DotsPaper::FoldAlongX(int x)
{
	auto it = std::partition(m_dots.begin(), m_dots.end(), [x](const auto& dot) { return dot.x < x; });

	std::vector<IntVector2> dotsToMirror(it, m_dots.end());
	m_dots.erase(it, m_dots.end());

	for (auto&& dot : dotsToMirror)
	{
		if (dot.x > x)
			AddDot(2 * x - dot.x, dot.y);
	}
}

void DotsPaper::FoldAlong(const Fold& fold)
{
	switch (fold.axis)
	{
	case Fold::Axis::X:
		FoldAlongX(fold.value);
		break;
	case Fold::Axis::Y:
		FoldAlongY(fold.value);
		break;
	}
}

std::istream& operator>>(std::istream& in, DotsPaper& paper)
{
	std::string line;
	while (std::getline(in, line) && !line.empty())
	{
		int x{};
		int y{};

		std::istringstream inLine(line);
		inLine >> x; 
		inLine.ignore();
		inLine >> y;

		paper.AddDot(x, y);
	}
	return in;
}

std::istream& operator>>(std::istream& in, std::vector<Fold>& folds)
{
	std::string line;
	while (std::getline(in, line))
	{
		constexpr size_t axisStart = std::size("fold along ") - 1u;// Sub 1 to ignore string ending '\0'.
		constexpr size_t valueStart = axisStart + 2;
		if (line.length() <= valueStart)
			continue;
		Fold::Axis axis = line[axisStart] == 'x' ? Fold::Axis::X : Fold::Axis::Y;
		int val = std::atoi(line.c_str() + valueStart);
		folds.emplace_back(axis, val);
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, DotsPaper& paper)
{
	int maxX = 0;
	int maxY = 0;
	for (const auto& dot : paper.m_dots)
	{
		maxX = std::max(dot.x, maxX);
		maxY = std::max(dot.y, maxY);
	}

	std::vector<std::string> lines;
	lines.resize(maxY + 1, std::string(maxX + 1, '.'));
	for (const auto& dot : paper.m_dots)
	{
		lines[dot.y][dot.x] = '#';
	}

	for (const auto& line : lines)
		out << line << std::endl;

	return out;
}
