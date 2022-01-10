#include "pch.h"
#include "Lanternfish.h"

#include <numeric>

void LanternfishPopulation::SetPopulation(int time, int64_t count)
{
	m_pouplation[time] = count;
}

int64_t LanternfishPopulation::CountAll() const
{
	return std::accumulate(m_pouplation.begin(), m_pouplation.end(), 0ULL);
}

int64_t LanternfishPopulation::Count(int timer) const
{
	return m_pouplation[timer];
}

void LanternfishPopulation::Grow(int steps)
{
	for (int s = 0; s < steps; ++s)
	{
		int64_t population0 = m_pouplation[0];
		for (std::size_t i = 1; i < TIMERS_COUNT; ++i)
		{
			m_pouplation[i - 1] = m_pouplation[i];
		}
		m_pouplation[6] += population0;
		m_pouplation[8] = population0;
	}
}

std::istream& operator>>(std::istream& in, LanternfishPopulation& population)
{
	int timer{};
	while (in >> timer)
	{
		population.SetPopulation(timer, population.Count(timer) + 1);
		in.ignore(1, ',');
	}
	return in;
}
