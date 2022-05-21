#include "pch.h"

#include "../Code/Cube.h"

#include <sstream>
#include <string>

namespace
{
	constexpr const char c_exampleInput[] = R"--(on x=10..12,y=10..12,z=10..12
on x=11..13,y=11..13,z=11..13
off x=9..11,y=9..11,z=9..11
on x=10..10,y=10..10,z=10..10)--";

	constexpr const char c_exampleInput2[] = R"--(on x=-20..26,y=-36..17,z=-47..7
on x=-20..33,y=-21..23,z=-26..28
on x=-22..28,y=-29..23,z=-38..16
on x=-46..7,y=-6..46,z=-50..-1
on x=-49..1,y=-3..46,z=-24..28
on x=2..47,y=-22..22,z=-23..27
on x=-27..23,y=-28..26,z=-21..29
on x=-39..5,y=-6..47,z=-3..44
on x=-30..21,y=-8..43,z=-13..34
on x=-22..26,y=-27..20,z=-29..19
off x=-48..-32,y=26..41,z=-47..-37
on x=-12..35,y=6..50,z=-50..-2
off x=-48..-32,y=-32..-16,z=-15..-5
on x=-18..26,y=-33..15,z=-7..46
off x=-40..-22,y=-38..-28,z=23..41
on x=-16..35,y=-41..10,z=-47..6
off x=-32..-23,y=11..30,z=-14..3
on x=-49..-5,y=-3..45,z=-29..18
off x=18..30,y=-20..-8,z=-3..13
on x=-41..9,y=-7..43,z=-33..15
on x=-54112..-39298,y=-85059..-49293,z=-27449..7877
on x=967..23432,y=45373..81175,z=27513..53682)--";
}

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

TEST(Day22, CubeMapOnOff)
{
	CubeMap map;

	map.On(Cube({ 1, 1, 1 }, { 1, 1, 1 }));
	EXPECT_EQ(map.Volume(), 1);

	map.On(Cube({ 2, 1, 1 }, { 2, 1, 1 }));
	EXPECT_EQ(map.Volume(), 2);

	map.On(Cube({ 1, 1, 1 }, { 2, 1, 1 }));
	EXPECT_EQ(map.Volume(), 2);

	map.On(Cube({ 1, 1, 1 }, { 3, 1, 1 }));
	EXPECT_EQ(map.Volume(), 3);

	map.Off(Cube({ 0, 1, 1 }, { 0, 1, 1 }));
	EXPECT_EQ(map.Volume(), 3);

	map.Off(Cube({ 1, 1, 1 }, { 1, 1, 1 }));
	EXPECT_EQ(map.Volume(), 2);
}

TEST(Day22, CubeMapFromExampleInput)
{
	CubeMap map;
	std::istringstream in(c_exampleInput);

	std::string op;
	Cube cube;

	while (in >> op >> cube)
	{
		if (op == "on")
			map.On(cube);
		else if (op == "off")
			map.Off(cube);
		else
			ASSERT_TRUE(false);
	}

	EXPECT_EQ(map.Volume(), 39);
}

TEST(Day22, CubeMapFromExampleInput2)
{
	CubeMap map;
	std::istringstream in(c_exampleInput2);

	std::string op;
	Cube cube;

	Cube region({ -50, -50, -50 }, { 50, 50, 50 });

	while (in >> op >> cube)
	{
		if (region.Intersection(cube) != cube)
			continue;

		if (op == "on")
			map.On(cube);
		else if (op == "off")
			map.Off(cube);
		else
			ASSERT_TRUE(false);
	}

	EXPECT_EQ(map.Volume(), 590784);
}
