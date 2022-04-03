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

TEST(Day17, GetXForcesReachingTargetOne)
{
	TrickShot::TargetArea area{ { 1, 1 }, { 1, 1 } };

	std::vector<int> xForces = TrickShot::GetXForces(area);

	EXPECT_EQ(xForces, std::vector<int>({ 1 }));
}

TEST(Day17, GetXForcesReachingTargetTwo)
{
	TrickShot::TargetArea area{ { 1, 1 }, { 2, 2 } };

	std::vector<int> xForces = TrickShot::GetXForces(area);

	EXPECT_EQ(xForces, std::vector<int>({ 1, 2 }));
}

TEST(Day17, GetYForcesReachingTargetOne)
{
	TrickShot::TargetArea area{ { 1, 1 }, { 1, 1 } };

	std::vector<int> xForces = TrickShot::GetYForces(area);

	EXPECT_EQ(xForces, std::vector<int>({ 1 }));
}

TEST(Day17, GetYForcesReachingTargetTwo)
{
	TrickShot::TargetArea area{ { 2, -2 }, { 2, -2 } };

	std::vector<int> xForces = TrickShot::GetYForces(area);

	EXPECT_EQ(xForces, std::vector<int>({ -2, 1 }));
}

TEST(Day17, GetYForcesReachingTargetPlusMinus)
{
	TrickShot::TargetArea area{ { 1, -5 }, { 1, 2 } };

	std::vector<int> xForces = TrickShot::GetYForces(area);

	EXPECT_EQ(xForces, std::vector<int>({ -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 }));
}

TEST(Day17, SimulateShotCheckIfReachesArea)
{
	TrickShot::TargetArea emptyArea{};
	IntVector2 zeroShot{};

	EXPECT_TRUE(TrickShot::SimuleteShot(zeroShot, emptyArea));
}

TEST(Day17, SimulateShotFailsInCannotHitArea)
{
	EXPECT_FALSE(TrickShot::SimuleteShot({ 0, 0 }, { { 1, 1 }, { 1, 1 } }));
}

TEST(Day17, SimulateShotExample)
{
	TrickShot::TargetArea exampleArea{ { 20, -10 }, { 30, -5 } };

	EXPECT_FALSE(TrickShot::SimuleteShot({ 0, 0 }, exampleArea));
	EXPECT_TRUE(TrickShot::SimuleteShot({ 7, 2 }, exampleArea));
	EXPECT_TRUE(TrickShot::SimuleteShot({ 6, 3 }, exampleArea));
	EXPECT_TRUE(TrickShot::SimuleteShot({ 9, 0 }, exampleArea));
	EXPECT_FALSE(TrickShot::SimuleteShot({ 17, -4 }, exampleArea));
	EXPECT_TRUE(TrickShot::SimuleteShot({ 6, 9 }, exampleArea));
	EXPECT_TRUE(TrickShot::SimuleteShot({ 7, 9 }, exampleArea));
}

TEST(Day17, FindHighestShot)
{
	TrickShot::TargetArea exampleArea{ { 20, -10 }, { 30, -5 } };

	EXPECT_EQ(TrickShot::FindHighestShot(exampleArea), IntVector2(7, 9));
}

TEST(Day17, GetShotHighestPosition)
{
	EXPECT_EQ(TrickShot::GetHighestPosition(0), 0);
	EXPECT_EQ(TrickShot::GetHighestPosition(1), 1);
	EXPECT_EQ(TrickShot::GetHighestPosition(9), 45);
	EXPECT_EQ(TrickShot::GetHighestPosition(-5), -5);
}

