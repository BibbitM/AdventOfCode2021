#include "pch.h"

#include "../Code/TrickShot.h"

#include <sstream>

namespace
{
	constexpr const char c_exampleInput[] = "target area: x=-10..20, y=-5..-1";
}

TEST(Day17, EmptyTargetArea)
{
	TrickShot::TargetArea emptyArea;

	EXPECT_EQ(emptyArea.GetMin().x, 0);
	EXPECT_EQ(emptyArea.GetMin().y, 0);
	EXPECT_EQ(emptyArea.GetMax().x, 0);
	EXPECT_EQ(emptyArea.GetMax().y, 0);
}

TEST(Day17, NotEmptyTargetArea)
{
	TrickShot::TargetArea area{ { -100, 2 }, { -10, 20 } };

	EXPECT_EQ(area.GetMin().x, -100);
	EXPECT_EQ(area.GetMin().y, 2);
	EXPECT_EQ(area.GetMax().x, -10);
	EXPECT_EQ(area.GetMax().y, 20);
}

TEST(Day17, TargetAreaFromStream)
{
	TrickShot::TargetArea area;
	std::istringstream input(c_exampleInput);

	input >> area;

	EXPECT_EQ(area.GetMin().x, -10);
	EXPECT_EQ(area.GetMin().y, -5);
	EXPECT_EQ(area.GetMax().x, 20);
	EXPECT_EQ(area.GetMax().y, -1);
}
