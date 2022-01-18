#include "pch.h"

#include "../Code/Heightmap.h"

#include <algorithm>
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

TEST(Day9, FindLowPointsEmpty)
{
	Heightmap heightmap;
	EXPECT_TRUE(heightmap.FindLowPoints().empty());
}

TEST(Day9, FindLowPointsSimple)
{
	std::istringstream input(c_simpleInput);
	Heightmap heightmap;

	input >> heightmap;

	EXPECT_EQ(heightmap.FindLowPoints(), std::vector<char>({ 1 }));
}

TEST(Day9, FindLowPointsExample)
{
	std::istringstream input(c_exampleInput);
	Heightmap heightmap;

	input >> heightmap;

	std::vector<char> lowPoints = heightmap.FindLowPoints();

	auto countOfCertaniValues = [](char val) { return [val](int acc, char v) -> int { return v == val ? acc + 1 : acc; }; };
	EXPECT_EQ(std::accumulate(lowPoints.begin(), lowPoints.end(), 0, countOfCertaniValues(1)), 1);
	EXPECT_EQ(std::accumulate(lowPoints.begin(), lowPoints.end(), 0, countOfCertaniValues(0)), 1);
	EXPECT_EQ(std::accumulate(lowPoints.begin(), lowPoints.end(), 0, countOfCertaniValues(5)), 2);
}

TEST(Day9, CalculateSumOfRiskLevelEmpty)
{
	Heightmap heightmap;
	EXPECT_EQ(heightmap.CalculateSumOfRiskLevel(), 0);
}

TEST(Day9, CalculateSumOfRiskLevelSimple)
{
	std::istringstream input(c_simpleInput);
	Heightmap heightmap;

	input >> heightmap;

	EXPECT_EQ(heightmap.CalculateSumOfRiskLevel(), 2);
}

TEST(Day9, CalculateSumOfRiskLevelExample)
{
	std::istringstream input(c_exampleInput);
	Heightmap heightmap;

	input >> heightmap;

	EXPECT_EQ(heightmap.CalculateSumOfRiskLevel(), 15);
}

TEST(Day9, FindLowPointsCoordsEmpty)
{
	Heightmap heightmap;
	EXPECT_TRUE(heightmap.FindLowPointsCoords().empty());
}

TEST(Day9, FindLowPointsCoordsSimple)
{
	std::istringstream input(c_simpleInput);
	Heightmap heightmap;

	input >> heightmap;

	EXPECT_EQ(heightmap.FindLowPointsCoords(), std::vector<Heightmap::Coord>({ { 0, 0 } }));
}

TEST(Day9, FindLowPointsCoordsExample)
{
	std::istringstream input(c_exampleInput);
	Heightmap heightmap;

	input >> heightmap;

	auto lowPointsCoords = heightmap.FindLowPointsCoords();
	EXPECT_EQ(lowPointsCoords.size(), 4);
	EXPECT_TRUE(std::find(lowPointsCoords.begin(), lowPointsCoords.end(), Heightmap::Coord(0, 1)) != lowPointsCoords.end());
	EXPECT_TRUE(std::find(lowPointsCoords.begin(), lowPointsCoords.end(), Heightmap::Coord(0, 9)) != lowPointsCoords.end());
	EXPECT_TRUE(std::find(lowPointsCoords.begin(), lowPointsCoords.end(), Heightmap::Coord(2, 2)) != lowPointsCoords.end());
	EXPECT_TRUE(std::find(lowPointsCoords.begin(), lowPointsCoords.end(), Heightmap::Coord(4, 6)) != lowPointsCoords.end());
}

TEST(Day9, FindBasinsEmpty)
{
	Heightmap heightmap;
	EXPECT_TRUE(heightmap.FindBasins().empty());
}

TEST(Day9, FindBasinsSimple)
{
	std::istringstream input(c_simpleInput);
	Heightmap heightmap;

	input >> heightmap;

	EXPECT_EQ(heightmap.FindBasins(), std::vector<int>({ 6 }));
}

TEST(Day9, FindBasinsExample)
{
	std::istringstream input(c_exampleInput);
	Heightmap heightmap;

	input >> heightmap;

	std::vector<int> basins = heightmap.FindBasins();
	EXPECT_EQ(basins.size(), 4);
	// Contains basins size.
	EXPECT_TRUE(std::find(basins.begin(), basins.end(), 3) != basins.end());
	EXPECT_TRUE(std::find(basins.begin(), basins.end(), 9) != basins.end());
	EXPECT_TRUE(std::find(basins.begin(), basins.end(), 14) != basins.end());
	// Basins size are sorted.
	EXPECT_EQ(basins[0], 14);
	EXPECT_EQ(basins[1], 9);
	EXPECT_EQ(basins[2], 9);
	EXPECT_EQ(basins[3], 3);
}

TEST(Day9, CalculateTop3BasinsMultiplyExample)
{
	std::istringstream input(c_exampleInput);
	Heightmap heightmap;

	input >> heightmap;

	std::vector<int> basins = heightmap.FindBasins();
	int top3BasinsMultiply = 1;
	for (size_t i = 0; i < std::min(basins.size(), 3ull); ++i)
		top3BasinsMultiply *= basins[i];

	EXPECT_EQ(top3BasinsMultiply, 1134);
}
