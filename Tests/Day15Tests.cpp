#include "pch.h"

#include "../Code/Cavern.h"

#include <sstream>

namespace
{
	constexpr const char c_exampleInput[] = R"--(1163751742
1381373672
2136511328
3694931569
7463417111
1319128137
1359912421
3125421639
1293138521
2311944581)--";
}

TEST(Day15, CreateEmptyCavern)
{
	Cavern cavern;

	EXPECT_EQ(cavern.GetSizeX(), 0);
	EXPECT_EQ(cavern.GetSizeY(), 0);
}

TEST(Day15, LoadCavernFromInput)
{
	Cavern cavern;
	std::istringstream input("123\n456\n");

	input >> cavern;

	ASSERT_EQ(cavern.GetSizeX(), 3);
	ASSERT_EQ(cavern.GetSizeY(), 2);
	EXPECT_EQ(cavern.Get(0, 0), 1);
	EXPECT_EQ(cavern.Get(1, 0), 2);
	EXPECT_EQ(cavern.Get(0, 1), 4);
	EXPECT_EQ(cavern.Get(2, 1), 6);
}

TEST(Day15, LoadCavernFromExample)
{
	Cavern cavern;
	std::istringstream input(c_exampleInput);

	input >> cavern;

	ASSERT_EQ(cavern.GetSizeX(), 10);
	ASSERT_EQ(cavern.GetSizeY(), 10);
	EXPECT_EQ(cavern.Get(0, 0), 1);
	EXPECT_EQ(cavern.Get(9, 0), 2);
	EXPECT_EQ(cavern.Get(6, 5), 8);
	EXPECT_EQ(cavern.Get(0, 9), 2);
	EXPECT_EQ(cavern.Get(9, 9), 1);
}

TEST(Day15, CalculateRiskIgnoresStartIncudesEnd)
{
	Cavern cavern;
	std::istringstream input("15\n");

	input >> cavern;

	EXPECT_EQ(cavern.CalculateRisk(), 5);
}

TEST(Day15, CalculateRiskSimple)
{
	Cavern cavern;
	std::istringstream input("19\n12");

	input >> cavern;

	EXPECT_EQ(cavern.CalculateRisk(), 3);
}

TEST(Day15, CalculateRiskExample)
{
	Cavern cavern;
	std::istringstream input(c_exampleInput);

	input >> cavern;

	EXPECT_EQ(cavern.CalculateRisk(), 40);
}
