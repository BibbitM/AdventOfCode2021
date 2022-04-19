#include "pch.h"
#include "DiracDice.h"

int Dirac::Game::Play()
{
	Dice dice;
	size_t currentPlayer = 0;
	while (true)
	{
		m_players[currentPlayer].Move(dice.Roll(3));
		if (m_players[currentPlayer].Score() >= 1000)
			break;
		currentPlayer = (currentPlayer + 1) % 2;
	}

	// Multiply the score of the losing player by the number of times the die was rolled during the game.
	return m_players[(currentPlayer + 1) % 2].Score() * dice.NumRolls();
}

std::istream& Dirac::operator>>(std::istream& in, Game& game)
{
	int player1Space{};
	int player2Space{};

	in.ignore(28); // Skip "Player 1 starting position: "
	in >> player1Space;
	in.ignore(28); // Skip "Player 2 starting position: "
	in >> player2Space;

	game.m_players[0] = Dirac::Player(player1Space);
	game.m_players[1] = Dirac::Player(player2Space);

	return in;
}
