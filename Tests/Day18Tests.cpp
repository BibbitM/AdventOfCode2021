#include "pch.h"

#include "../Code/SnailfishNumber.h"

TEST(Day18, EmptyNumberHasZeroMagnitude)
{
	Snailfish::Number empty;

	EXPECT_EQ(empty.Magnitude(), 0);
}
