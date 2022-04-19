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

TEST(Day21, DiracDiceRollWrapAround100)
{
	Dirac::Dice dice;

	dice.Roll(98);
	EXPECT_EQ(dice.Roll(), 99);
	EXPECT_EQ(dice.Roll(), 100);
	EXPECT_EQ(dice.Roll(), 1);
	EXPECT_EQ(dice.Roll(3), 2 + 3 + 4);
	dice.Roll(500);
	EXPECT_EQ(dice.Roll(), 5);
}

TEST(Day21, DiracPlayerEmpty)
{
	Dirac::Player player;

	EXPECT_EQ(player.Score(), 0);
}
