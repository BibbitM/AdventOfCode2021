#include "pch.h"

#include "../Code/Cube.h"

#include <sstream>
#include <string>

TEST(Day22, EmptyCube)
{
	const Cube cube{};

	EXPECT_EQ(cube.Volume(), 1);
}

TEST(Day22, CubeCtor)
{
	EXPECT_EQ(Cube({ 0, 0, 0 }, { 0, 0, 0 }).Volume(), 1);
	EXPECT_EQ(Cube({ 0, 0, 0 }, { 1, 0, 0 }).Volume(), 2);
	EXPECT_EQ(Cube({ 0, 0, 0 }, { 1, 1, 0 }).Volume(), 4);
	EXPECT_EQ(Cube({ 0, 0, 0 }, { 1, 1, 1 }).Volume(), 8);
	EXPECT_EQ(Cube({ -1, -1, -1 }, { 1, 1, 1 }).Volume(), 27);
}

TEST(Day22, BigCubeVolume)
{
	EXPECT_EQ(Cube({ 1, 1, 1 }, { 10'000, 10'000, 10'000 }).Volume(), 1'000'000'000'000);
}

TEST(Day22, LoadInput)
{
	std::istringstream in("on x=10..12,y=10..12,z=10..12");

	std::string op;
	Cube cube;

	in >> op >> cube;

	EXPECT_EQ(op, "on");
	EXPECT_EQ(cube, Cube({ 10, 10, 10 }, { 12, 12, 12 }));
}
