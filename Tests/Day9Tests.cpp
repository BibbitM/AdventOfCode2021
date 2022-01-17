#include "pch.h"

#include "../Code/Heightmap.h"

#include <numeric>
#include <sstream>

namespace
{
	constexpr char c_simpleInput[] = "123\n456";
	constexpr char c_exampleInput[] = R"--(2199943210
3987894921
9856789892
8767896789
9899965678)--";
}

TEST(Day9, LoadSimpleHeightmap)
{
	std::istringstream input(c_simpleInput);
	Heightmap heightmap;

	input >> heightmap;

	EXPECT_EQ(heightmap.GetRows(), 2);
	EXPECT_EQ(heightmap.GetColumns(), 3);
	EXPECT_EQ(heightmap[0][0], 1);
	EXPECT_EQ(heightmap[0][1], 2);
	EXPECT_EQ(heightmap[0][2], 3);
	EXPECT_EQ(heightmap[1][0], 4);
	EXPECT_EQ(heightmap[1][1], 5);
	EXPECT_EQ(heightmap[1][2], 6);
}

TEST(Day9, LoadExampleInput)
{
	std::istringstream input(c_exampleInput);
	Heightmap heightmap;

	input >> heightmap;

	EXPECT_EQ(heightmap.GetRows(), 5);
	EXPECT_EQ(heightmap.GetColumns(), 10);
	EXPECT_EQ(heightmap[0][0], 2);
	EXPECT_EQ(heightmap[3][3], 7);
	EXPECT_EQ(heightmap[4][9], 8);
}

TEST(Day9, GetLowPointsSimple)
{
	std::istringstream input(c_simpleInput);
	Heightmap heightmap;

	input >> heightmap;

	EXPECT_EQ(heightmap.GetLowPoints(), std::vector<char>({ 1 }));
}

TEST(Day9, GetLowPointsExample)
{
	std::istringstream input(c_exampleInput);
	Heightmap heightmap;

	input >> heightmap;

	std::vector<char> lowPoints = heightmap.GetLowPoints();

	auto countOfCertaniValues = [](char val) { return [val](int acc, char v) -> int { return v == val ? acc + 1 : acc; }; };
	EXPECT_EQ(std::accumulate(lowPoints.begin(), lowPoints.end(), 0, countOfCertaniValues(1)), 1);
	EXPECT_EQ(std::accumulate(lowPoints.begin(), lowPoints.end(), 0, countOfCertaniValues(0)), 1);
	EXPECT_EQ(std::accumulate(lowPoints.begin(), lowPoints.end(), 0, countOfCertaniValues(5)), 2);
}
