#include "pch.h"

#include "../Code/OctopusGrid.h"
#include "../Code/Utils.h"

#include <sstream>

namespace
{
	constexpr const char c_exampleInput[] = R"--(5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526)--";
}

TEST(Day11, CreateEmptyOctopusGrid)
{
	OctopusGrid grid;
	UNUSED(grid);
}

TEST(Day11, SetAndGetOctopusEnergy)
{
	OctopusGrid grid;

	EXPECT_EQ(grid.Get({ 0, 0 }), 0);

	grid.Set({ 0, 0 }, 1);
	grid.Set({ 3, 4 }, 3);
	grid.Set({ 9, 9 }, 9);

	EXPECT_EQ(grid.Get({ 0, 0 }), 1);
	EXPECT_EQ(grid.Get({ 3, 4 }), 3);
	EXPECT_EQ(grid.Get({ 9, 9 }), 9);
}

TEST(Day11, IsValidPosInOctopusGrid)
{
	OctopusGrid grid;

	EXPECT_TRUE(grid.IsValid({ 0, 0 }));
	EXPECT_TRUE(grid.IsValid({ 3, 9 }));
	EXPECT_TRUE(grid.IsValid({ 9, 2 }));

	EXPECT_FALSE(grid.IsValid({ -1, 0 }));
	EXPECT_FALSE(grid.IsValid({ 0, -1 }));
	EXPECT_FALSE(grid.IsValid({ -11, -23 }));

	EXPECT_FALSE(grid.IsValid({ 10, 0 }));
	EXPECT_FALSE(grid.IsValid({ 0, 10 }));
	EXPECT_FALSE(grid.IsValid({ 123, 456 }));

	EXPECT_FALSE(grid.IsValid({ -123, 456 }));
}

TEST(Day11, StepIncreasesEnergy)
{
	OctopusGrid grid;
	const IntVector2 pos{ 1, 3 };

	grid.Set(pos, 1);
	grid.Step();
	EXPECT_EQ(grid.Get(pos), 2);
	grid.Step(3);
	EXPECT_EQ(grid.Get(pos), 5);
}

TEST(Day11, MaximalEnergyResetsAfterStep)
{
	{
		OctopusGrid grid;
		const IntVector2 pos{ 4, 8 };

		grid.Set(pos, 9);
		grid.Step();
		EXPECT_EQ(grid.Get(pos), 0);
	}

	{
		OctopusGrid grid;
		const IntVector2 pos{ 3, 7 };

		grid.Set(pos, 8);
		grid.Step(4);
		EXPECT_EQ(grid.Get(pos), 2);
	}
}

TEST(Day11, FlashIncreaseNeighoursEnergy)
{
	OctopusGrid grid;
	const IntVector2 pos{ 5, 5 };

	grid.Set(pos, 9);
	grid.Step();
	EXPECT_EQ(grid.Get(pos), 0);
	EXPECT_EQ(grid.Get({ pos.x - 1, pos.y - 1 }), 2);
	EXPECT_EQ(grid.Get({ pos.x - 1, pos.y }), 2);
	EXPECT_EQ(grid.Get({ pos.x - 1, pos.y + 1 }), 2);
	EXPECT_EQ(grid.Get({ pos.x, pos.y - 1 }), 2);
	EXPECT_EQ(grid.Get({ pos.x, pos.y + 1 }), 2);
	EXPECT_EQ(grid.Get({ pos.x + 1, pos.y - 1 }), 2);
	EXPECT_EQ(grid.Get({ pos.x + 1, pos.y }), 2);
	EXPECT_EQ(grid.Get({ pos.x + 1, pos.y + 1 }), 2);
}

TEST(Day11, IncreasedEnergyAfterNeightourFlashCausesAnoterFlash)
{
	OctopusGrid grid;
	const IntVector2 pos1{ 3, 4 };
	const IntVector2 pos2{ 4, 5 };

	grid.Set(pos1, 9);
	grid.Set(pos2, 8);
	grid.Step();
	EXPECT_EQ(grid.Get(pos1), 0);
	EXPECT_EQ(grid.Get(pos2), 0);
}

TEST(Day11, OctopusGridCountsFlashes)
{
	OctopusGrid grid;
	EXPECT_EQ(grid.GetFlashes(), 0);
	const IntVector2 pos{ 2, 2 };
	grid.Set(pos, 9);
	grid.Step();
	EXPECT_EQ(grid.GetFlashes(), 1);
}

TEST(Day11, OctopusGridReadsFromStream)
{
	OctopusGrid grid;
	std::istringstream input{ c_exampleInput };
	input >> grid;

	EXPECT_EQ(grid.Get({ 0, 0 }), 5);
	EXPECT_EQ(grid.Get({ 9, 9 }), 6);
	EXPECT_EQ(grid.Get({ 8, 1 }), 1);
}

TEST(Day11, OctopusGridExampleStep)
{
	OctopusGrid grid;
	std::istringstream input{ c_exampleInput };
	input >> grid;

	grid.Step(100);
	EXPECT_EQ(grid.GetFlashes(), 1656);
}

TEST(Day11, OctopusGridFlashesAllTogether)
{
	OctopusGrid grid;
	for (int y = 0; y < OctopusGrid::c_gridSize; ++y)
		for (int x = 0; x < OctopusGrid::c_gridSize; ++x)
			grid.Set({ x, y }, 8);

	grid.Step();
	EXPECT_FALSE(grid.AllFlashed());
	grid.Step();
	EXPECT_TRUE(grid.AllFlashed());
}

TEST(Day11, OctopusGridCountsSteps)
{
	OctopusGrid grid;
	EXPECT_EQ(grid.GetSteps(), 0);
	grid.Step();
	EXPECT_EQ(grid.GetSteps(), 1);
	grid.Step(10);
	EXPECT_EQ(grid.GetSteps(), 11);
}

TEST(Day11, OctopusGridExampleAllFlashed)
{
	OctopusGrid grid;
	std::istringstream input{ c_exampleInput };
	input >> grid;

	while (!grid.AllFlashed())
	{
		grid.Step();
	}
	EXPECT_EQ(grid.GetSteps(), 195);
}
