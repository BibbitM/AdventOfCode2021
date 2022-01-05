#include "pch.h"

#include "../Code/Bingo.h"

#include <array>
#include <vector>

namespace
{
	const int c_boardValues[5][5] = {
		{ 11, 12, 13, 14, 15 },
		{ 21, 22, 23, 24, 25 },
		{ 31, 32, 33, 34, 35 },
		{ 41, 45, 43, 44, 45 },
		{ 51, 52, 53, 54, 55 }
	};

	const std::array<std::vector<short int>, 2> c_arrayOfArraysOfShorts = { std::vector<short int>{ 11, 12 }, std::vector<short int>{ 21, 22 } };
}

TEST(Day4, CreateEmptyBingoBoard)
{
	Bingo emptyBingoBoard;

	EXPECT_TRUE(emptyBingoBoard.Check(0));
	EXPECT_FALSE(emptyBingoBoard.Check(10));
}

TEST(Day4, CreateBingoBoardFromDefinedNumbers)
{
	Bingo bingoBoardFromIntArray(c_boardValues);

	EXPECT_TRUE(bingoBoardFromIntArray.Check(21));
	EXPECT_FALSE(bingoBoardFromIntArray.Check(2));
}

TEST(Day4, CreateBingoBoardFromTwoDimensionArray)
{
	Bingo bingoBoardFromIntArray(c_arrayOfArraysOfShorts);

	EXPECT_TRUE(bingoBoardFromIntArray.Check(11));
	EXPECT_FALSE(bingoBoardFromIntArray.Check(2));
}

TEST(Day4, MatchFiveInRowGivesBingo)
{
	Bingo board(c_boardValues);

	EXPECT_FALSE(board.Match(11));
	EXPECT_FALSE(board.Match(12));
	EXPECT_FALSE(board.Match(13));
	EXPECT_FALSE(board.Match(14));
	EXPECT_TRUE(board.Match(15));
}

TEST(Day4, MatchFiveInColumnGivesBingo)
{
	Bingo board(c_boardValues);

	EXPECT_FALSE(board.Match(13));
	EXPECT_FALSE(board.Match(23));
	EXPECT_FALSE(board.Match(53));
	EXPECT_FALSE(board.Match(43));
	EXPECT_TRUE(board.Match(33));
}

TEST(Day4, MatchFiveDiagonalDoesNotGivesBingo)
{
	Bingo board(c_boardValues);

	EXPECT_FALSE(board.Match(11));
	EXPECT_FALSE(board.Match(22));
	EXPECT_FALSE(board.Match(33));
	EXPECT_FALSE(board.Match(44));
	EXPECT_FALSE(board.Match(55));
}

TEST(Day4, MatchFiveNotCreatingLineDoesNotGivesBingo)
{
	Bingo board(c_boardValues);

	EXPECT_FALSE(board.Match(11));
	EXPECT_FALSE(board.Match(32));
	EXPECT_FALSE(board.Match(31));
	EXPECT_FALSE(board.Match(42));
	EXPECT_FALSE(board.Match(12));
}

TEST(Day4, EmptyBoardSumOfUnmatchedGivesZero)
{
	Bingo emptyBoard;

	EXPECT_EQ(emptyBoard.SumOfUnmatched(), 0);
}

TEST(Day4, TestBoardSumOfUnmatched)
{
	Bingo board(c_boardValues);

	EXPECT_EQ(board.SumOfUnmatched(), 828);
}

TEST(Day4, TestBoardSumOfUnmatchedIgnoresMatches)
{
	Bingo board(c_boardValues);

	board.Match(13);
	board.Match(15);

	EXPECT_EQ(board.SumOfUnmatched(), 800);
}
