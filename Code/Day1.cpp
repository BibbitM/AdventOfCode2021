#include "pch.h"

#include <istream>
#include <limits>
#include <string>
#include <vector>

std::vector<int> LoadIntStream(std::istream& in)
{
	std::vector<int> intVector;
	std::string line;
	while (std::getline(in, line))
	{
		intVector.push_back(std::stoi(line));
	}
	return intVector;
}

int GetIncreasedMeasurements(std::vector<int> measurements)
{
	int increased = 0;
	for (int i = 1; i < measurements.size(); ++i)
	{
		int prev = measurements[i - 1] ;
		int curr =                     measurements[i - 0];
		if (curr > prev)
			++increased;
	}
	return increased;
}

int GetIncreasedThreeMeasurements(std::vector<int> measurements)
{
	int increased = 0;
	for (int i = 3; i < measurements.size(); ++i)
	{
		int prev = measurements[i - 3] /*+ measurements[i - 2] + measurements[i - 1]*/;
		int curr =                       /*measurements[i - 2] + measurements[i - 1] +*/ measurements[i - 0];
		if (curr > prev)
			++increased;
	}
	return increased;
}
