#include "pch.h"

#include "../Code/DotsPaper.h"

#include <sstream>

namespace
{
	constexpr const char c_exampleInput[] = R"--(6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5)--";
}

TEST(Day13, PaperEmpty)
{
	DotsPaper paper;
	EXPECT_EQ(paper.CountDots(), 0);
}

TEST(Day13, PaperAddingDots)
{
	DotsPaper paper;
	paper.AddDot(0, 0);
	EXPECT_EQ(paper.CountDots(), 1);
	paper.AddDot(10, 100);
	paper.AddDot(3, 4);
	EXPECT_EQ(paper.CountDots(), 3);
}

TEST(Day13, PaperAddingTheSameDotsTwiceCountsOnec)
{
	DotsPaper paper;
	paper.AddDot(1, 2);
	paper.AddDot(1, 2);
	EXPECT_EQ(paper.CountDots(), 1);
}

TEST(Day13, PaperFoldingHorizontally)
{
	DotsPaper paper;
	paper.AddDot(0, 1);
	paper.AddDot(0, 3); // Overlaps with (0, 1) after folding
	paper.FoldAlongY(2);
	EXPECT_EQ(paper.CountDots(), 1);
}

TEST(Day13, PaperFoldingVertically)
{
	DotsPaper paper;
	paper.AddDot(2, 1);
	paper.AddDot(3, 1);
	paper.AddDot(6, 1); // Overlaps with (6, 1) after folding
	paper.FoldAlongX(4);
	EXPECT_EQ(paper.CountDots(), 2);
}

TEST(Day13, PaperAndFoldsLoadFromExampleStream)
{
	DotsPaper paper;
	std::istringstream input{ c_exampleInput };
	input >> paper;
	EXPECT_EQ(paper.CountDots(), 18);

	std::vector<Fold> folds;
	input >> folds;
	ASSERT_EQ(folds.size(), 2);
	paper.FoldAlong(folds[0]);
	EXPECT_EQ(paper.CountDots(), 17);
	paper.FoldAlong(folds[1]);
	EXPECT_EQ(paper.CountDots(), 16);
}

TEST(Day13, PaperEmptyPrint)
{
	DotsPaper paper;

	std::ostringstream output;
	output << paper;
	EXPECT_EQ(output.str(), ".\n");
}

TEST(Day13, PaperSimplePrint)
{
	DotsPaper paper;
	paper.AddDot(0, 0);
	paper.AddDot(1, 1);
	paper.AddDot(0, 2);
	paper.AddDot(1, 2);

	std::ostringstream output;
	output << paper;
	EXPECT_EQ(output.str(), "#.\n.#\n##\n");
}
