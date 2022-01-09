#include "pch.h"

#include "../Code/BingoBoard.h"
#include "../Code/BingoCard.h"
#include "../Code/BingoNumbers.h"
#include "../Code/Utils.h"

#include <array>
#include <sstream>
#include <vector>

namespace
{
	constexpr int c_boardValues[5][5] = {
		{ 11, 12, 13, 14, 15 },
		{ 21, 22, 23, 24, 25 },
		{ 31, 32, 33, 34, 35 },
		{ 41, 45, 43, 44, 45 },
		{ 51, 52, 53, 54, 55 }
	};
	constexpr int c_boardPlus100Values[5][5] = {
		{ 111, 112, 113, 114, 115 },
		{ 121, 122, 123, 124, 125 },
		{ 131, 132, 133, 134, 135 },
		{ 141, 145, 143, 144, 145 },
		{ 151, 152, 153, 154, 155 }
	};

	const std::array<std::vector<short int>, 2> c_arrayOfArraysOfShorts = { std::vector<short int>{ 11, 12 }, std::vector<short int>{ 21, 22 } };

	constexpr char c_exampleInputString[] = R"--(7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7)--";

	constexpr int c_exampleInputNumbers[] = { 7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1 };

	constexpr int c_exampleInputFirstBoardValues[5][5] = {
		{ 22, 13, 17, 11,  0 },
		{  8,  2, 23,  4, 24 },
		{ 21,  9, 14, 16,  7 },
		{  6, 10,  3, 18,  5 },
		{  1, 12, 20, 15, 19 }
	};
}

TEST(Day4, CreateEmptyBingoBoard)
{
	BingoBoard emptyBingoBoard;

	EXPECT_TRUE(emptyBingoBoard.Check(0));
	EXPECT_FALSE(emptyBingoBoard.Check(10));
}

TEST(Day4, CreateBingoBoardFromDefinedNumbers)
{
	BingoBoard bingoBoardFromIntArray(c_boardValues);

	EXPECT_TRUE(bingoBoardFromIntArray.Check(21));
	EXPECT_FALSE(bingoBoardFromIntArray.Check(2));
}

TEST(Day4, CreateBingoBoardFromTwoDimensionArray)
{
	BingoBoard bingoBoardFromIntArray(c_arrayOfArraysOfShorts);

	EXPECT_TRUE(bingoBoardFromIntArray.Check(11));
	EXPECT_FALSE(bingoBoardFromIntArray.Check(2));
}

TEST(Day4, MatchFiveInRowGivesBingo)
{
	BingoBoard board(c_boardValues);

	EXPECT_FALSE(board.Match(11));
	EXPECT_FALSE(board.Match(12));
	EXPECT_FALSE(board.Match(13));
	EXPECT_FALSE(board.Match(14));
	EXPECT_TRUE(board.Match(15));
}

TEST(Day4, MatchFiveInColumnGivesBingo)
{
	BingoBoard board(c_boardValues);

	EXPECT_FALSE(board.Match(13));
	EXPECT_FALSE(board.Match(23));
	EXPECT_FALSE(board.Match(53));
	EXPECT_FALSE(board.Match(43));
	EXPECT_TRUE(board.Match(33));
}

TEST(Day4, MatchFiveDiagonalDoesNotGivesBingo)
{
	BingoBoard board(c_boardValues);

	EXPECT_FALSE(board.Match(11));
	EXPECT_FALSE(board.Match(22));
	EXPECT_FALSE(board.Match(33));
	EXPECT_FALSE(board.Match(44));
	EXPECT_FALSE(board.Match(55));
}

TEST(Day4, MatchFiveNotCreatingLineDoesNotGivesBingo)
{
	BingoBoard board(c_boardValues);

	EXPECT_FALSE(board.Match(11));
	EXPECT_FALSE(board.Match(32));
	EXPECT_FALSE(board.Match(31));
	EXPECT_FALSE(board.Match(42));
	EXPECT_FALSE(board.Match(12));
}

TEST(Day4, EmptyBoardSumOfUnmatchedGivesZero)
{
	BingoBoard emptyBoard;

	EXPECT_EQ(emptyBoard.SumOfUnmatched(), 0);
}

TEST(Day4, TestBoardSumOfUnmatched)
{
	BingoBoard board(c_boardValues);

	EXPECT_EQ(board.SumOfUnmatched(), 828);
}

TEST(Day4, TestBoardSumOfUnmatchedIgnoresMatches)
{
	BingoBoard board(c_boardValues);

	board.Match(13);
	board.Match(15);

	EXPECT_EQ(board.SumOfUnmatched(), 800);
}

TEST(Day4, CreateEmptyBingoCard)
{
	BingoCard emptyBingoCard;

	UNUSED(emptyBingoCard);
}

TEST(Day4, PlayOnBingoCardWithVectorOfNumbersNoWiner)
{
	BingoCard bingoCard;
	BingoBoard bingoBoard(c_boardValues);

	bingoCard.AddBoard(bingoBoard);

	std::vector<int> numbers{ 1, 2, 3 };

	EXPECT_EQ(bingoCard.Play(numbers), BingoCard::INVALID_POINTS);
}

TEST(Day4, PlayOnBingoCardWithVectorOfNumbersAndWin)
{
	BingoCard bingoCard;
	BingoBoard bingoBoard(c_boardValues);

	bingoCard.AddBoard(bingoBoard);

	std::vector<int> numbers{ 21, 22, 23, 24, 25 };

	EXPECT_EQ(bingoCard.Play(numbers), 17825);
}

TEST(Day4, PlayOnBingoCardTwoBoarsWithVectorOfNumbersAndWin)
{
	BingoCard bingoCard;
	bingoCard.AddBoard(BingoBoard(c_boardPlus100Values));
	bingoCard.AddBoard(BingoBoard(c_boardValues));

	std::vector<int> numbers{ 1, 22, 124, 23, 24, 122, 123, 125, 25, 121 };

	EXPECT_EQ(bingoCard.Play(numbers), 328273);
}

TEST(Day4, LoadExampleNumbersAndBoard)
{
	std::istringstream input{ c_exampleInputString };

	BingoNumbers numbers;
	input >> numbers;

	EXPECT_EQ(numbers.AsVector(), std::vector(std::begin(c_exampleInputNumbers), std::end(c_exampleInputNumbers)));

	BingoBoard board;
	input >> board;

	EXPECT_EQ(board, BingoBoard(c_exampleInputFirstBoardValues));
}

TEST(Day4, RunBingoOnExampleInput)
{
	std::istringstream input{ c_exampleInputString };

	BingoNumbers numbers;
	input >> numbers;

	BingoCard card;
	for (BingoBoard board; input >> board; )
	{
		card.AddBoard(board);
	}

	EXPECT_EQ(card.Play(numbers.AsVector()), 4512);
}

TEST(Day4, RunBingoOnExampleInputTillLastWin)
{
	std::istringstream input{ c_exampleInputString };

	BingoNumbers numbers;
	input >> numbers;

	BingoCard card;
	for (BingoBoard board; input >> board; )
	{
		card.AddBoard(board);
	}

	EXPECT_EQ(card.PlayTillLast(numbers.AsVector()), 1924);
}
