#include "pch.h"

#include "../Code/DiracDice.h"

TEST(Day21, DiracDiceEmpty)
{
	Dirac::Dice dice;
	
	EXPECT_EQ(dice.NumRolls(), 0);
}

TEST(Day21, DiracDiceRollReturns)
{
	Dirac::Dice dice;

	EXPECT_EQ(dice.Roll(), 1);
	EXPECT_EQ(dice.Roll(), 2);
	EXPECT_EQ(dice.Roll(), 3);
	EXPECT_EQ(dice.NumRolls(), 3);
}

TEST(Day21, DiracDiceRollNTimsReturnSumOfRolls)
{
	Dirac::Dice dice;

	EXPECT_EQ(dice.Roll(3), 1 + 2 + 3);
	EXPECT_EQ(dice.Roll(1), 4);
	EXPECT_EQ(dice.Roll(6), 5 + 6 + 7 + 8 + 9 + 10);
	EXPECT_EQ(dice.NumRolls(), 10);
}
