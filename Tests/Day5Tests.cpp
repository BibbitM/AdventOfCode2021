#include "pch.h"

#include "../Code/IntLine2.h"
#include "../Code/Utils.h"

extern std::vector<IntLine2> LoadLinesStream(std::istream& in);
extern int CountDangerousPoints(const std::vector<IntLine2>& lines);
extern int CountDangerousPointsWithDiagonal(const std::vector<IntLine2>& lines);

namespace
{
	constexpr char c_exampleInput[] = R"--(0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2)--";

	constexpr IntLine2 c_exampleLines[]
	{
		{ { 0, 9 }, { 5, 9 } },
		{ { 8, 0 }, { 0, 8 } },
		{ { 9, 4 }, { 3, 4 } },
		{ { 2, 2 }, { 2, 1 } },
		{ { 7, 0 }, { 7, 4 } },
		{ { 6, 4 }, { 2, 0 } },
		{ { 0, 9 }, { 2, 9 } },
		{ { 3, 4 }, { 1, 4 } },
		{ { 0, 0 }, { 8, 8 } },
		{ { 5, 5 }, { 8, 2 } }
	};
}

TEST(Day5, EmptyLine)
{
	IntLine2 emptyLine{};

	EXPECT_EQ(emptyLine.first, IntVector2(0, 0));
	EXPECT_EQ(emptyLine.second, IntVector2(0, 0));
}

TEST(Day5, LineFromPoints)
{
	IntLine2 line(IntVector2(0, 0), IntVector2(1, 1));

	EXPECT_EQ(line.first, IntVector2(0, 0));
	EXPECT_EQ(line.second, IntVector2(1, 1));
}

TEST(Day5, LoadingLineFromString)
{
	std::istringstream input("1,2 -> 3,4");
	IntLine2 line{};

	input >> line;

	EXPECT_EQ(line, IntLine2({ 1,2 }, { 3,4 }));
}

TEST(Day5, LoadExampleInput)
{
	std::istringstream input(c_exampleInput);
	std::vector<IntLine2> lines;
	IntLine2 l;
	while (input >> l)
	{
		lines.push_back(l);
	}

	EXPECT_EQ(lines, std::vector<IntLine2>(std::begin(c_exampleLines), std::end(c_exampleLines)));
}

TEST(Day5, LoadExampleLinesStream)
{
	std::istringstream input(c_exampleInput);
	std::vector<IntLine2> lines = LoadLinesStream(input);

	EXPECT_EQ(lines, std::vector<IntLine2>(std::begin(c_exampleLines), std::end(c_exampleLines)));
}

TEST(Day5, CountDangerousPointsFromEmptyLines)
{
	EXPECT_EQ(CountDangerousPoints(std::vector<IntLine2>()), 0);
}

TEST(Day5, CountDangerousPointsFromExampleInput)
{
	std::vector<IntLine2> lines(std::begin(c_exampleLines), std::end(c_exampleLines));
	EXPECT_EQ(CountDangerousPoints(lines), 5);
}

TEST(Day5, CountDangerousPointsWithDiagonalFromExampleInput)
{
	std::vector<IntLine2> lines(std::begin(c_exampleLines), std::end(c_exampleLines));
	EXPECT_EQ(CountDangerousPointsWithDiagonal(lines), 12);
}
