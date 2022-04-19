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
