#pragma once

namespace Dirac
{
	class Dice
	{
	public:
		int NumRolls() const { return m_numRolls; }

		int Roll() { ++m_numRolls; return m_nextRoll++; }

	private:
		int m_numRolls{ 0 };
		int m_nextRoll{ 1 };
	};
}
