#include "pch.h"

#include "../Code/Cave.h"

#include <sstream>

TEST(Day12, EmptyCaveGivesZeroPath)
{
	CavesMap map;
	EXPECT_EQ(map.FindDistinctPathsCount(), 0);
}

TEST(Day12, CreateSimpleCaveWithOnePath)
{
	CavesMap map;
	map.AddConnection("start", "end");
	EXPECT_EQ(map.FindDistinctPathsCount(), 1);
}

TEST(Day12, CreateCaveWithTwoPaths)
{
	CavesMap map;
	map.AddConnection("start", "A");
	map.AddConnection("start", "B");
	map.AddConnection("A", "end");
	map.AddConnection("B", "end");
	EXPECT_EQ(map.FindDistinctPathsCount(), 2);
}

TEST(Day12, CreateCaveWithDeadEndAndTwoPats)
{
	CavesMap map;
	map.AddConnection("start", "A");
	map.AddConnection("A", "b");
	map.AddConnection("A", "end");
	EXPECT_EQ(map.FindDistinctPathsCount(), 2);
}

TEST(Day12, Example1FindDistinctPathsCount)
{
	CavesMap map;
	std::istringstream input(R"--(start-A
start-b
A-c
A-b
b-d
A-end
b-end)--");

	input >> map;
	EXPECT_EQ(map.FindDistinctPathsCount(), 10);
}

TEST(Day12, Example2FindDistinctPathsCount)
{
	CavesMap map;
	std::istringstream input(R"--(dc-end
HN-start
start-kj
dc-start
dc-HN
LN-dc
HN-end
kj-sa
kj-HN
kj-dc)--");

	input >> map;
	EXPECT_EQ(map.FindDistinctPathsCount(), 19);
}

TEST(Day12, Example3FindDistinctPathsCount)
{
	CavesMap map;
	std::istringstream input(R"--(fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW)--");

	input >> map;
	EXPECT_EQ(map.FindDistinctPathsCount(), 226);
}
