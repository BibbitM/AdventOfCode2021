#include "pch.h"
#include "DiracDice.h"

#include <numeric>

static_assert(std::accumulate(Dirac::QuantumDice::s_moveUniversers.begin(), Dirac::QuantumDice::s_moveUniversers.end(), 0u, [](uint32_t v, const auto& e) { return v + e.second; }) == 3u * 3u * 3u);

uint32_t Dirac::Game::GetHash() const
{
	return
		(static_cast<uint32_t>(m_players[0].Space()) << 24) |
		(static_cast<uint32_t>(m_players[0].Score()) << 16) |
		(static_cast<uint32_t>(m_players[1].Space()) <<  8) |
		(static_cast<uint32_t>(m_players[1].Score()) <<  0);
}

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

uint64_t Dirac::Game::PlayQuantum(int pointsLimit) const
{
	uint64_t playerWins[2] = {};

	PlayQuantum(0, playerWins, 1, pointsLimit);

	return std::max(playerWins[0], playerWins[1]);
}

void Dirac::Game::PlayQuantum(size_t currentPlayer, uint64_t (&playerWins)[2], uint64_t universes, int pointsLimit) const
{
	for (const auto& moveUnivers : QuantumDice::s_moveUniversers)
	{
		Game gameUniverse{ *this };
		gameUniverse.m_players[currentPlayer].Move(moveUnivers.first);
		if (gameUniverse.m_players[currentPlayer].Score() >= pointsLimit)
			playerWins[currentPlayer] += universes * moveUnivers.second;
		else
			gameUniverse.PlayQuantum((currentPlayer + 1) % 2, playerWins, universes * moveUnivers.second, pointsLimit);
	}
}

uint64_t Dirac::Game::PlayQuantumWithCache(int pointsLimit) const
{
	std::unordered_map<uint32_t, std::array<uint64_t, 2>> winsCache;

	const auto& playerWins = PlayQuantumWithCache(winsCache, pointsLimit);

	return std::max(playerWins[0], playerWins[1]);
}

std::array<uint64_t, 2> Dirac::Game::PlayQuantumWithCache(std::unordered_map<uint32_t, std::array<uint64_t, 2>>& winsCache, int pointsLimit) const
{
	const uint32_t hash = GetHash();
	auto foundIt = winsCache.find(hash);
	if (foundIt != winsCache.end())
		return foundIt->second;

	std::array<uint64_t, 2> playerWins{};

	for (const auto& moveUnivers : QuantumDice::s_moveUniversers)
	{
		Game gameUniverse{ *this };
		gameUniverse.m_players[0].Move(moveUnivers.first);
		if (gameUniverse.m_players[0].Score() >= pointsLimit)
			playerWins[0] += moveUnivers.second;
		else
		{
			Game nextGameUniverse(gameUniverse.m_players[1], gameUniverse.m_players[0]);
			auto nextPlayeWins = nextGameUniverse.PlayQuantumWithCache(winsCache, pointsLimit);
			playerWins[0] += nextPlayeWins[1] * moveUnivers.second;
			playerWins[1] += nextPlayeWins[0] * moveUnivers.second;
		}
	}

	winsCache.insert(make_pair(hash, playerWins));

	return playerWins;
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
