#include "pch.h"

#include <algorithm>
#include <deque>
#include <limits>
#include <vector>

int GetAlignFuelCost(const std::vector<int>& crabs)
{
	std::vector<int> sortedCrabs = crabs;
	std::sort(sortedCrabs.begin(), sortedCrabs.end());
	struct PositionWithCount
	{
		int position;
		int count;
	};
	std::deque<PositionWithCount> positionsWithCount;
	for (std::size_t i = 0; i < sortedCrabs.size(); )
	{
		int pos = sortedCrabs[i];
		int count = 0;
		for ( ; i < sortedCrabs.size() && pos == sortedCrabs[i]; ++i, ++count)
		{
		}
		positionsWithCount.emplace_back(pos, count);
	}

	int fuelCost = 0;
	while (positionsWithCount.size() > 1)
	{
		const std::size_t last = positionsWithCount.size() - 1;
		if (positionsWithCount[0].count < positionsWithCount[last].count)
		{
			const int dist = positionsWithCount[1].position - positionsWithCount[0].position;
			fuelCost += dist * positionsWithCount[0].count;
			positionsWithCount[1].count += positionsWithCount[0].count;
			positionsWithCount.pop_front();
		}
		else
		{
			const int dist = positionsWithCount[last].position - positionsWithCount[last - 1].position;
			fuelCost += dist * positionsWithCount[last].count;
			positionsWithCount[last - 1].count += positionsWithCount[last].count;
			positionsWithCount.pop_back();
		}
	}

	return fuelCost;
}
