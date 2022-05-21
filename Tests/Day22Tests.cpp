#include "pch.h"

#include "../Code/Cube.h"

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
