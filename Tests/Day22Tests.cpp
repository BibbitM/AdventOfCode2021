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

TEST(Day22, LoadCubeFromInput)
{
	std::istringstream in("on x=10..12,y=10..12,z=10..12");

	std::string op;
	Cube cube;

	in >> op >> cube;

	EXPECT_EQ(op, "on");
	EXPECT_EQ(cube, Cube({ 10, 10, 10 }, { 12, 12, 12 }));
}

TEST(Day22, CubeIntersection)
{
	// Empty
	EXPECT_EQ(Cube({ 1, 1, 1 }, { 1, 1, 1 }).Intersection(Cube({ 10, 10, 10 }, { 12, 12, 12 })).Volume(), 0);

	// The same.
	{
		const Cube cube({ 1, 1, 1 }, { 10, 10, 10 });
		EXPECT_EQ(cube.Intersection(cube), cube);
	}

	// Included.
	{
		const Cube inside({ 5, 5, 5 }, { 6, 7, 8 });
		const Cube outside({ 0, 0, 0 }, { 10, 10, 10 });

		EXPECT_EQ(inside.Intersection(outside), inside);
		EXPECT_EQ(outside.Intersection(inside), inside);
	}

	// Side.
	{
		const Cube cube({ 0, 0, 0 }, { 5, 5, 5 });
		const Cube right({ 1, 1, 1 }, { 10, 3, 3 });

		EXPECT_EQ(cube.Intersection(right), Cube({ 1, 1, 1 }, { 5, 3, 3 }));
	}

	// Corner.
	{
		const Cube cube({ 0, 0, 0 }, { 5, 5, 5 });
		const Cube right({ -5, -5, -5 }, { 1, 2, 3 });

		EXPECT_EQ(cube.Intersection(right), Cube({ 0, 0, 0 }, { 1, 2, 3 }));
	}
}

TEST(Day22, CubeMapEmpty)
{
	const CubeMap map;

	EXPECT_EQ(map.Volume(), 0);
}
