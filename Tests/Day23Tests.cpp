#include "pch.h"

#include "../Code/Amphipods.h"

TEST(Day23, CreateDefaultAmphipodsBurrow)
{
	Amphipods::Burrow burrow;
	EXPECT_TRUE(burrow.IsOrganized());
}

TEST(Day23, CreateOrganizedAmphipodsBurrow)
{
	Amphipods::Burrow burrow("ABCD"
							 "ABCD");
	EXPECT_TRUE(burrow.IsOrganized());
}

TEST(Day23, CreateUnorganizedAmphipodsBurrow)
{
	Amphipods::Burrow burrow("ABCD"
							 "DCBA");
	EXPECT_FALSE(burrow.IsOrganized());
}

TEST(Day23, WeCanMoveAmphipodsToHallway)
{
	Amphipods::Burrow burrow("BCBD"
							 "ADCA");

	EXPECT_NE(burrow.MoveToHallway(0, 0), 0);
	EXPECT_NE(burrow.MoveToHallway(1, 10), 0);
	EXPECT_NE(burrow.MoveToHallway(2, 1), 0);
	EXPECT_NE(burrow.MoveToHallway(3, 9), 0);
}

TEST(Day23, MoveAmphipodsToHallwayReturnsUsedEnergy)
{
	Amphipods::Burrow burrow("ABCD"
							 "DCBA");

	// First row.
	EXPECT_EQ(burrow.MoveToHallway(0, 0), 3);
	EXPECT_EQ(burrow.MoveToHallway(1, 10), 70);
	EXPECT_EQ(burrow.MoveToHallway(2, 1), 600);
	EXPECT_EQ(burrow.MoveToHallway(3, 9), 2000);

	// Second row.
	EXPECT_EQ(burrow.MoveToHallway(0, 7), 7000);
	EXPECT_EQ(burrow.MoveToHallway(1, 3), 300);
	EXPECT_EQ(burrow.MoveToHallway(2, 5), 30);
}
