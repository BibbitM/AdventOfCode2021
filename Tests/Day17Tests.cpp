#include "pch.h"

#include "../Code/TrickShot.h"

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
