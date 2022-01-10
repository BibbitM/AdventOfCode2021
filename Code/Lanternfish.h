#pragma once

#include <array>
#include <istream>

class LanternfishPopulation
{
public:
	static constexpr std::size_t TIMERS_COUNT = 8 + 1;

	LanternfishPopulation() = default;
	LanternfishPopulation(const int (&counts)[8]);

	void SetPopulation(int time, int64_t count);
	int64_t CountAll() const;
	int64_t Count(int timer) const;

	void Grow(int steps = 1);

private:
	std::array<int64_t, TIMERS_COUNT> m_pouplation{};
};

std::istream& operator>>(std::istream& in, LanternfishPopulation& population);
