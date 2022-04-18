#pragma once

#include "IntVector2.h"

#include <iostream>
#include <vector>

struct Fold;

class DotsPaper
{
public:
	int CountDots() const { return static_cast<int>(m_dots.size()); }

	void AddDot(int x, int y);
	void FoldAlongY(int y);
	void FoldAlongX(int x);
	void FoldAlong(const Fold& fold);

private:
	std::vector<IntVector2> m_dots;
	friend std::ostream& operator<<(std::ostream& out, const DotsPaper& paper);
};

struct Fold
{
	enum class Axis { X, Y };
	Axis axis;
	int value;

};

std::istream& operator>>(std::istream& in, DotsPaper& paper);
std::ostream& operator<<(std::ostream& out, const DotsPaper& paper);
std::istream& operator>>(std::istream& in, std::vector<Fold>& folds);
