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
