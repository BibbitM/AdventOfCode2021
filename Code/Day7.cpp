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

int GetAlignRealFuelCost(const std::vector<int>& crabs)
{
	std::vector<int> sortedCrabs = crabs;
	std::sort(sortedCrabs.begin(), sortedCrabs.end());
	struct PositionWithCount
	{
		int position;
		int count;
		int cost;
	};
	std::deque<PositionWithCount> positionsWithCount;
	for (std::size_t i = 0; i < sortedCrabs.size(); )
	{
		int pos = sortedCrabs[i];
		int count = 0;
		for (; i < sortedCrabs.size() && pos == sortedCrabs[i]; ++i, ++count)
		{
		}
		positionsWithCount.emplace_back(pos, count, 0);
	}

	auto MoveCost = [](const PositionWithCount& pwc) { return pwc.count + pwc.cost; };

	int fuelCost = 0;
	while (positionsWithCount.size() > 1)
	{
		const std::size_t last = positionsWithCount.size() - 1;
		if (MoveCost(positionsWithCount[0]) < MoveCost(positionsWithCount[last]))
		{
			fuelCost += MoveCost(positionsWithCount[0]);
			if (positionsWithCount[1].position == positionsWithCount[0].position + 1)
			{
				positionsWithCount[1].count += positionsWithCount[0].count;
				positionsWithCount[1].cost += MoveCost(positionsWithCount[0]);
				positionsWithCount.pop_front();
			}
			else
			{
				positionsWithCount[0].position += 1;
				positionsWithCount[0].cost += positionsWithCount[0].count;
			}
		}
		else
		{
			fuelCost += MoveCost(positionsWithCount[last]);
			if (positionsWithCount[last - 1].position == positionsWithCount[last].position - 1)
			{
				positionsWithCount[last - 1].count += positionsWithCount[last].count;
				positionsWithCount[last - 1].cost += MoveCost(positionsWithCount[last]);
				positionsWithCount.pop_back();
			}
			else
			{
				positionsWithCount[last].position -= 1;
				positionsWithCount[last].cost += positionsWithCount[last].count;
			}
		}
	}

	return fuelCost;
}
