#include "pch.h"

#include "../Code/Cube.h"

TEST(Day22, EmptyCube)
{
	const Cube cube{};

	EXPECT_EQ(cube.Volume(), 0);
}
