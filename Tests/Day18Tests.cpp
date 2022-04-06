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
