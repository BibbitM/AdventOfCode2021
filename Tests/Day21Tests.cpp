#include "pch.h"

#include "../Code/DiracDice.h"
#include "../Code/Utils.h"

#include <sstream>

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

	EXPECT_EQ(player.Space(), 1);
	EXPECT_EQ(player.Score(), 0);
}

TEST(Day21, DiracPlayerAtGivenSpace)
{
	Dirac::Player player(3);

	EXPECT_EQ(player.Space(), 3);
	EXPECT_EQ(player.Score(), 0);
}

TEST(Day21, DiracPlayerMovesInSpace)
{
	Dirac::Player player(1);
	player.Move(3);
	EXPECT_EQ(player.Space(), 1 + 3);
	player.Move(5);
	EXPECT_EQ(player.Space(), 9);
}

TEST(Day21, DiracPlayerMovesWrapArround10)
{
	Dirac::Player player(10);
	player.Move(1);
	EXPECT_EQ(player.Space(), 1);
	player.Move(10);
	EXPECT_EQ(player.Space(), 1);
	player.Move(205);
	EXPECT_EQ(player.Space(), 6);
}

TEST(Day21, DiracPlayerAddScoreAfterMove)
{
	Dirac::Player player(5);
	player.Move(1);
	EXPECT_EQ(player.Space(), 6);
	EXPECT_EQ(player.Score(), 0 + 6);
	player.Move(10);
	EXPECT_EQ(player.Space(), 6);
	EXPECT_EQ(player.Score(), 6 + 6);
	player.Move(2);
	EXPECT_EQ(player.Space(), 8);
	EXPECT_EQ(player.Score(), 12 + 8);
	player.Move(3);
	EXPECT_EQ(player.Space(), 1);
	EXPECT_EQ(player.Score(), 20 + 1);
}

TEST(Day21, DiracGameEmpty)
{
	Dirac::Game game;
	UNUSED(game);
}

TEST(Day21, DiracGamePlaysTill1000AndReturnsLoosingScore)
{
	Dirac::Game game(4, 8);
	EXPECT_EQ(game.Play(), 739785);
}

TEST(Day21, DiracGameLoadFromInput)
{
	Dirac::Game game;
	std::istringstream input(
		"Player 1 starting position: 5\n"
		"Player 2 starting position: 3\n");

	input >> game;

	EXPECT_EQ(game.Play(), Dirac::Game(5, 3).Play());
}

TEST(Day21, DiracGamePlaysQuantumTill10AndReturnWinnersCount)
{
	Dirac::Game game(4, 8);
	EXPECT_EQ(game.PlayQuantum(10), 18'973'591ull);
}

TEST(Day21, DiracGamePlaysQuantumWithCacheTill10AndReturnWinnersCount)
{
	Dirac::Game game(4, 8);
	EXPECT_EQ(game.PlayQuantumWithCache(10), 18'973'591ull);
}

TEST(Day21, DiracGamePlaysQuantumWithCacheTill21AndReturnWinnersCount)
{
	Dirac::Game game(4, 8);
	EXPECT_EQ(game.PlayQuantumWithCache(21), std::max(444'356'092'776'315ull, 341'960'390'180'808ull));
}
