#include "pch.h"

#include "../Code/Lanternfish.h"
#include "../Code/Utils.h"

#include <sstream>

namespace
{
	constexpr char c_exampleInput[] = "3,4,3,1,2";
}

TEST(Day6, CreateEmptyLanternfishPopulation)
{
	LanternfishPopulation emptyPopulation;
	UNUSED(emptyPopulation);

	EXPECT_EQ(emptyPopulation.Count(0), 0);
	EXPECT_EQ(emptyPopulation.Count(1), 0);
	EXPECT_EQ(emptyPopulation.Count(2), 0);
	EXPECT_EQ(emptyPopulation.Count(3), 0);
	EXPECT_EQ(emptyPopulation.Count(4), 0);
	EXPECT_EQ(emptyPopulation.Count(5), 0);
	EXPECT_EQ(emptyPopulation.Count(6), 0);
	EXPECT_EQ(emptyPopulation.Count(7), 0);
	EXPECT_EQ(emptyPopulation.Count(8), 0);
	EXPECT_EQ(emptyPopulation.CountAll(), 0);
}

TEST(Day6, CreateLanternfishPopulation)
{
	LanternfishPopulation population;
	population.SetPopulation(0, 10);
	population.SetPopulation(1, 1);
	population.SetPopulation(2, 2);
	population.SetPopulation(3, 3);
	population.SetPopulation(4, 4);
	population.SetPopulation(5, 5);
	population.SetPopulation(6, 6);
	population.SetPopulation(7, 7);
	population.SetPopulation(8, 8);

	EXPECT_EQ(population.Count(0), 10);
	EXPECT_EQ(population.Count(1), 1);
	EXPECT_EQ(population.Count(2), 2);
	EXPECT_EQ(population.Count(3), 3);
	EXPECT_EQ(population.Count(4), 4);
	EXPECT_EQ(population.Count(5), 5);
	EXPECT_EQ(population.Count(6), 6);
	EXPECT_EQ(population.Count(7), 7);
	EXPECT_EQ(population.Count(8), 8);
	EXPECT_EQ(population.CountAll(), 46);
}

TEST(Day6, LanternfishUpdatesTimeReducesTimeToSpawnWithGrow)
{
	{
		LanternfishPopulation population;
		population.SetPopulation(5, 1);
		EXPECT_EQ(population.Count(5), 1);
		EXPECT_EQ(population.Count(4), 0);
		population.Grow();
		EXPECT_EQ(population.Count(5), 0);
		EXPECT_EQ(population.Count(4), 1);
	}

	{
		LanternfishPopulation population;
		population.SetPopulation(3, 30);
		population.SetPopulation(4, 40);
		EXPECT_EQ(population.Count(2), 0);
		EXPECT_EQ(population.Count(3), 30);
		EXPECT_EQ(population.Count(4), 40);
		population.Grow();
		EXPECT_EQ(population.Count(2), 30);
		EXPECT_EQ(population.Count(3), 40);
		EXPECT_EQ(population.Count(4), 0);
	}
}

TEST(Day6, LanternfishWithTimer0Duplicates)
{
	LanternfishPopulation population;
	population.SetPopulation(0, 5);
	EXPECT_EQ(population.Count(0), 5);
	EXPECT_EQ(population.Count(6), 0);
	EXPECT_EQ(population.Count(8), 0);
	EXPECT_EQ(population.CountAll(), 5);
	population.Grow();
	EXPECT_EQ(population.Count(0), 0);
	EXPECT_EQ(population.Count(6), 5);
	EXPECT_EQ(population.Count(8), 5);
	EXPECT_EQ(population.CountAll(), 10);
}

TEST(Day6, LanternfishGrowAcceptsNumStepsToGrow)
{
	LanternfishPopulation population;
	population.SetPopulation(5, 5);
	EXPECT_EQ(population.Count(2), 0);
	EXPECT_EQ(population.Count(5), 5);
	population.Grow(3);
	EXPECT_EQ(population.Count(2), 5);
	EXPECT_EQ(population.Count(5), 0);
}

TEST(Day6, LanternfishGrowClearsLast)
{
	LanternfishPopulation population;
	population.SetPopulation(8, 10);
	EXPECT_EQ(population.Count(8), 10);
	population.Grow();
	EXPECT_EQ(population.Count(8), 0);
}

TEST(Day6, LoadPopulationFromSimpleInput)
{
	LanternfishPopulation population;
	std::istringstream input{ "1,2,5,3,5,3,3" };
	input >> population;
	EXPECT_EQ(population.Count(1), 1);
	EXPECT_EQ(population.Count(2), 1);
	EXPECT_EQ(population.Count(3), 3);
	EXPECT_EQ(population.Count(5), 2);
}

TEST(Day6, LoadPopulationFromExampleInput)
{
	LanternfishPopulation population;
	std::istringstream input(c_exampleInput);
	input >> population;
	EXPECT_EQ(population.Count(0), 0);
	EXPECT_EQ(population.Count(1), 1);
	EXPECT_EQ(population.Count(2), 1);
	EXPECT_EQ(population.Count(3), 2);
	EXPECT_EQ(population.Count(4), 1);
	EXPECT_EQ(population.Count(5), 0);
	EXPECT_EQ(population.Count(6), 0);
	EXPECT_EQ(population.Count(7), 0);
	EXPECT_EQ(population.Count(8), 0);
	EXPECT_EQ(population.CountAll(), 5);
}

TEST(Day6, GrowExamplePopulationFor18Days)
{
	LanternfishPopulation population;
	std::istringstream input(c_exampleInput);
	input >> population;
	population.Grow(18);
	EXPECT_EQ(population.CountAll(), 26);
}

TEST(Day6, GrowExamplePopulationFor80Days)
{
	LanternfishPopulation population;
	std::istringstream input(c_exampleInput);
	input >> population;
	population.Grow(80);
	EXPECT_EQ(population.CountAll(), 5934);
}

TEST(Day6, GrowExamplePopulationFor256Days)
{
	LanternfishPopulation population;
	std::istringstream input(c_exampleInput);
	input >> population;
	population.Grow(256);
	EXPECT_EQ(population.CountAll(), 26984457539);
}
