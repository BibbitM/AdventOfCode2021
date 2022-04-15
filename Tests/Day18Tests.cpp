#include "pch.h"

#include "../Code/SnailfishNumber.h"

TEST(Day18, EmptyNumberHasZeroMagnitude)
{
	Snailfish::Number empty;
	EXPECT_EQ(empty.Magnitude(), 0);
}

TEST(Day18, SimpleNumberMagnitude)
{
	EXPECT_EQ(Snailfish::Number(0, 0).Magnitude(), 0);
	EXPECT_EQ(Snailfish::Number(5, 0).Magnitude(), 5 * 3);
	EXPECT_EQ(Snailfish::Number(0, 4).Magnitude(), 4 * 2);
	EXPECT_EQ(Snailfish::Number(9, 1).Magnitude(), 29);
	EXPECT_EQ(Snailfish::Number(1, 9).Magnitude(), 21);
}

TEST(Day18, CompareNumbers)
{
	EXPECT_EQ(Snailfish::Number(0, 0), Snailfish::Number());
	EXPECT_EQ(Snailfish::Number(1, 2), Snailfish::Number(1, 2));

	EXPECT_NE(Snailfish::Number(9, 9), Snailfish::Number());
	EXPECT_NE(Snailfish::Number(5, 3), Snailfish::Number(2, 1));
}

TEST(Day18, CreateSimpleNumberFromString)
{
	EXPECT_EQ(Snailfish::Number("[0,0]"), Snailfish::Number(0, 0));
	EXPECT_EQ(Snailfish::Number("[4,2]"), Snailfish::Number(4, 2));
}

TEST(Day18, ConvertNumberToString)
{
	EXPECT_EQ(Snailfish::Number("[0,0]").ToString(), "[0,0]");
	EXPECT_EQ(Snailfish::Number("[1,2]").ToString(), "[1,2]");
	EXPECT_EQ(Snailfish::Number("[[[[0,9],2],3],4]").ToString(), "[[[[0,9],2],3],4]");
	EXPECT_EQ(Snailfish::Number("[[1,2],[3,4]]").ToString(), "[[1,2],[3,4]]");
}

TEST(Day18, CreateNumberFromStringLiteral)
{
	EXPECT_EQ("[1,2]"_SN, Snailfish::Number(1, 2));
	EXPECT_EQ("[[1,2],[3,[[4,5],6]]]"_SN, Snailfish::Number("[[1,2],[3,[[4,5],6]]]"));
}

TEST(Day18, AddSimpleNumbersMagnitude)
{
	EXPECT_EQ((Snailfish::Number("[0,0]") + Snailfish::Number("[0,0]")).Magnitude(), 0);
	EXPECT_EQ((Snailfish::Number("[1,0]") + Snailfish::Number("[0,2]")).Magnitude(), 17);
}

TEST(Day18, SimpleSumCreatesComplexNumber)
{
	EXPECT_EQ(Snailfish::Number("[0,0]") + Snailfish::Number("[0,0]"), Snailfish::Number("[[0,0],[0,0]]"));
	EXPECT_EQ(Snailfish::Number("[1,2]") + Snailfish::Number("[3,4]"), Snailfish::Number("[[1,2],[3,4]]"));
}

TEST(Day18, ExplodeComplexNumberToString)
{
	EXPECT_EQ(Snailfish::Number("[[[[[9,8],1],2],3],4]").ToString(), "[[[[0,9],2],3],4]");
	EXPECT_EQ(Snailfish::Number("[7,[6,[5,[4,[3,2]]]]]").ToString(), "[7,[6,[5,[7,0]]]]");
	EXPECT_EQ(Snailfish::Number("[[6,[5,[4,[3,2]]]],1]").ToString(), "[[6,[5,[7,0]]],3]");
	// Partial reductions steps.
	//EXPECT_EQ(Snailfish::Number("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]").ToString(), "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]");
	//EXPECT_EQ(Snailfish::Number("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]").ToString(), "[[3,[2,[8,0]]],[9,[5,[7,0]]]]");
	EXPECT_EQ(Snailfish::Number("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]").ToString(), "[[3,[2,[8,0]]],[9,[5,[7,0]]]]");
	EXPECT_EQ(Snailfish::Number("[[[[[2,3],4],5],6],[[[[3,7],1],2],3]]").ToString(), "[[[[0,7],5],9],[[[0,8],2],3]]");
}

TEST(Day18, ExplodeComplexNumber)
{
	EXPECT_EQ(Snailfish::Number("[[[[[9,8],1],2],3],4]"), Snailfish::Number("[[[[0,9],2],3],4]"));
	EXPECT_EQ(Snailfish::Number("[7,[6,[5,[4,[3,2]]]]]"), Snailfish::Number("[7,[6,[5,[7,0]]]]"));
	EXPECT_EQ(Snailfish::Number("[[6,[5,[4,[3,2]]]],1]"), Snailfish::Number("[[6,[5,[7,0]]],3]"));
	EXPECT_EQ(Snailfish::Number("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]"), Snailfish::Number("[[3,[2,[8,0]]],[9,[5,[7,0]]]]"));
}

TEST(Day18, SplitSimpleNumber)
{
	EXPECT_EQ(Snailfish::Number("[10,1]").ToString(), "[[5,5],1]");
	EXPECT_EQ(Snailfish::Number("[2,11]").ToString(), "[2,[5,6]]");
}

TEST(Day18, SplitAndReduceExampleNumberToString)
{
	EXPECT_EQ(Snailfish::Number("[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]").ToString(), "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
}

TEST(Day18, AddSplitAndReduceExampleNubers)
{
	EXPECT_EQ(Snailfish::Number("[[[[4,3],4],4],[7,[[8,4],9]]]") + Snailfish::Number("[1,1]"), Snailfish::Number("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]"));
}
