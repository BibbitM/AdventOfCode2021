#pragma once

#include <array>
#include <istream>

class LanternfishPopulation
{
public:
	static constexpr std::size_t TIMERS_COUNT = 8 + 1;

	LanternfishPopulation() = default;
	LanternfishPopulation(const int (&counts)[8]);

	void SetPopulation(int time, int count);
	int CountAll() const;
	int Count(int timer) const;

	void Grow(int steps = 1);

private:
	std::array<int, TIMERS_COUNT> m_pouplation{};
};

std::istream& operator>>(std::istream& in, LanternfishPopulation& population);
