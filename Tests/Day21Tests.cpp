#include "pch.h"

#include "../Code/DiracDice.h"

TEST(Day21, DiracDiceEmpty)
{
	Dirac::Dice dice;
	
	EXPECT_EQ(dice.NumRolls(), 0);
}
