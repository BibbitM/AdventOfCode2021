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
}
