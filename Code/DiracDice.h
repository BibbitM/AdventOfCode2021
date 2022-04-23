#pragma once

#include <array>
#include <istream>
#include <unordered_map>

namespace Dirac
{
	class Dice
	{
	public:
		int NumRolls() const { return m_numRolls; }

		int Roll(int count = 1)
		{
			int roll = 0;
			for (int i = 0; i < count; ++i)
			{
				++m_numRolls;
				roll += m_nextRoll++;
				if (m_nextRoll > 100)
					m_nextRoll -= 100;
			}
			return roll;
		}

	private:
		int m_numRolls{ 0 };
		int m_nextRoll{ 1 };
	};

	class QuantumDice
	{
	public:
		static constexpr std::array<std::pair<int, uint32_t>, 9> s_moveUniversers = { {
			{ 3, 1 }, // 111
			{ 4, 3 }, // 112, 121, 211
			{ 5, 6 }, // 113, 131, 311, 122, 212, 221
			{ 6, 7 }, // 123, 132, 213, 231, 312, 221, 222
			{ 7, 6 }, // 331, 313, 133, 322, 323, 223
			{ 8, 3 }, // 331, 131, 133
			{ 9, 1 }, // 333
		} };
	};

	class Player
	{
	public:
		Player() = default;
		Player(int space) : m_space(space) { }

		int Space() const { return m_space; }
		int Score() const { return m_score; }

		void Move(int distance)
		{
			m_space = (m_space + distance - 1) % 10 + 1;
			m_score += m_space;
		}

	private:
		int m_space{ 1 };
		int m_score{ 0 };
	};

	class Game
	{
	public:
		Game() = default;
		Game(int player1Space, int player2Space)
			: m_players{ Player(player1Space), Player(player2Space) }
		{ }
		Game(const Player& player1, const Player& player2)
			: m_players{ player1, player2 }
		{ }

		uint32_t GetHash() const;

		int Play();
		uint64_t PlayQuantum(int pointsLimit) const;
		uint64_t PlayQuantumWithCache(int pointsLimit) const;

	private:
		std::array<Player, 2> m_players{};

		void PlayQuantum(size_t currentPlayer, uint64_t (&playerWins)[2], uint64_t universes, int pointsLimit) const;
		std::array<uint64_t, 2> PlayQuantumWithCache(std::unordered_map<uint32_t, std::array<uint64_t, 2>>& winsCache, int pointsLimit) const;

		friend std::istream& operator>>(std::istream& in, Game& game);
	};

	std::istream& operator>>(std::istream& in, Dirac::Game& game);
}
