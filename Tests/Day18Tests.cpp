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
