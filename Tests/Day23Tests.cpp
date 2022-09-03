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

TEST(Day23, MoveAmphipodsToHallwayChangesBurrow)
{
	Amphipods::Burrow burrow("ABCD"
							 "DCBA");
	Amphipods::Burrow prevBurrow;

	prevBurrow = burrow;
	EXPECT_EQ(burrow.MoveToHallway(0, 0), 3);
	EXPECT_NE(burrow, prevBurrow);

	prevBurrow = burrow;
	EXPECT_EQ(burrow.MoveToHallway(1, 10), 70);
	EXPECT_NE(burrow, prevBurrow);
}

TEST(Day23, WeCanNotMoveAmphipodsToHallwayInFrontOfRoomsExit)
{
	Amphipods::Burrow burrow("ABCD"
		"DCBA");
	const Amphipods::Burrow orgBurrow = burrow;

	EXPECT_EQ(burrow.MoveToHallway(0, 2), 0);
	EXPECT_EQ(burrow, orgBurrow);
	EXPECT_EQ(burrow.MoveToHallway(0, 8), 0);
	EXPECT_EQ(burrow, orgBurrow);
	EXPECT_EQ(burrow.MoveToHallway(1, 4), 0);
	EXPECT_EQ(burrow, orgBurrow);
	EXPECT_EQ(burrow.MoveToHallway(2, 8), 0);
	EXPECT_EQ(burrow, orgBurrow);
	EXPECT_EQ(burrow.MoveToHallway(3, 6), 0);
	EXPECT_EQ(burrow, orgBurrow);
}

TEST(Day23, WeCanNotMoveAmphipodsToHallwayIfTargetIsOccupied)
{
	Amphipods::Burrow burrow("ABCD"
							 "DCBA");
	burrow.MoveToHallway(0, 0);

	const Amphipods::Burrow prevBurrow = burrow;
	EXPECT_EQ(burrow.MoveToHallway(0, 0), 0);
	EXPECT_EQ(burrow, prevBurrow);
}

TEST(Day23, WeCanNotMoveAmphipodsToHallwayIfThereAreOtherAmphipodsOnTheWay)
{
	Amphipods::Burrow burrow("ABCD"
							 "DCBA");

	burrow.MoveToHallway(0, 1);
	EXPECT_EQ(burrow.MoveToHallway(0, 0), 0);

	burrow.MoveToHallway(3, 9);
	EXPECT_EQ(burrow.MoveToHallway(3, 10), 0);

	burrow.MoveToHallway(3, 5);
	EXPECT_EQ(burrow.MoveToHallway(2, 3), 0);
	EXPECT_EQ(burrow.MoveToHallway(1, 7), 0);
}

TEST(Day23, WeCanNotMoveAmphipodsToHallwayIfThereIsNoMoreAmphipodsInTheRoom)
{
	Amphipods::Burrow burrow("ABCD"
							 "DCBA");
	burrow.MoveToHallway(0, 0);
	burrow.MoveToHallway(0, 1);

	const Amphipods::Burrow prevBurrow = burrow;
	EXPECT_EQ(burrow.MoveToHallway(0, 3), 0);
	EXPECT_EQ(burrow, prevBurrow);
}

TEST(Day23, WeCanMoveAmphipodsToHalfEmptyRoom)
{
	Amphipods::Burrow burrow("ABDC"
							 "ABCD");
	burrow.MoveToHallway(3, 9);
	burrow.MoveToHallway(2, 7);

	EXPECT_EQ(burrow.MoveToRoom(7, 3), 2000);
}

TEST(Day23, WeCanMoveAmphipodsToEmptyRoom)
{
	Amphipods::Burrow burrow("ABCD"
							 "DCBA");
	burrow.MoveToHallway(1, 0);
	burrow.MoveToHallway(2, 7);
	burrow.MoveToHallway(2, 1);
	burrow.MoveToHallway(1, 5);

	EXPECT_EQ(burrow.MoveToRoom(7, 2), 300);
	EXPECT_EQ(burrow.MoveToRoom(5, 2), 200);
}

TEST(Day23, WeCanNotMoveAmphipodsToFullRoom)
{
	Amphipods::Burrow burrow("ABCD"
							 "DCBA");
	burrow.MoveToHallway(3, 9);
	burrow.MoveToHallway(3, 3);

	EXPECT_EQ(burrow.MoveToRoom(3, 0), 0);
}

TEST(Day23, WeCanNotMoveAmphipodsToInvalidRoom)
{
	Amphipods::Burrow burrow("DABC"
							 "ABCD");
	burrow.MoveToHallway(0, 1);
	burrow.MoveToHallway(1, 3);
	burrow.MoveToHallway(2, 5);
	burrow.MoveToHallway(3, 7);

	EXPECT_EQ(burrow.MoveToRoom(1, 0), 0);
	EXPECT_EQ(burrow.MoveToRoom(3, 1), 0);
	EXPECT_EQ(burrow.MoveToRoom(5, 2), 0);
	EXPECT_EQ(burrow.MoveToRoom(7, 3), 0);
}

TEST(Day23, WeCanNotMoveAmphipodsIfOccupiedByWrongType)
{
	Amphipods::Burrow burrow("DABC"
							 "DABC");
	burrow.MoveToHallway(0, 1);
	burrow.MoveToHallway(1, 3);

	EXPECT_EQ(burrow.MoveToRoom(3, 0), 0);
}

TEST(Day23, WeCanNotMoveAmphipodsIfRoadIsBlocked)
{
	Amphipods::Burrow burrow("DABC"
							 "ABCD");
	burrow.MoveToHallway(0, 3);
	burrow.MoveToHallway(1, 5);

	EXPECT_EQ(burrow.MoveToRoom(5, 0), 0);
}

TEST(Day23, TestMoveCostCalculationWithTheExample)
{
	Amphipods::Burrow burrow("BCBD"
							 "ADCA");

	EXPECT_EQ(burrow.MoveToHallway(2, 3), 40);

	EXPECT_EQ(burrow.MoveToHallway(1, 5), 200);
	EXPECT_EQ(burrow.MoveToRoom(5, 2), 200);

	EXPECT_EQ(burrow.MoveToHallway(1, 5), 3000);
	EXPECT_EQ(burrow.MoveToRoom(3, 1), 30);

	EXPECT_EQ(burrow.MoveToHallway(0, 3), 20);
	EXPECT_EQ(burrow.MoveToRoom(3, 1), 20);

	EXPECT_EQ(burrow.MoveToHallway(3, 7), 2000);
	EXPECT_EQ(burrow.MoveToHallway(3, 9), 3);

	EXPECT_EQ(burrow.MoveToRoom(7, 3), 3000);
	EXPECT_EQ(burrow.MoveToRoom(5, 3), 4000);

	EXPECT_EQ(burrow.MoveToRoom(9, 0), 8);

	EXPECT_TRUE(burrow.IsOrganized());
}
