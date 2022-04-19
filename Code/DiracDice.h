#pragma once

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

	};
}
