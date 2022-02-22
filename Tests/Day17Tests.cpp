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
