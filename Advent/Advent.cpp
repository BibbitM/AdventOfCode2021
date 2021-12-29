#include "../Code/IntVector2.h"
#include <iostream>
#include <fstream>
#include <vector>

extern std::vector<int> LoadIntStream(std::istream& in);
extern int GetIncreasedMeasurements(std::vector<int> measurements);
extern int GetIncreasedThreeMeasurements(std::vector<int> measurements);

extern std::vector<IntVector2> LoadSubmarineCommandsStream(std::istream& in);

int main()
{
	{
		std::vector<int> measurements;

		{
			std::ifstream ifile("..\\Inputs\\Day1.txt");
			measurements = LoadIntStream(ifile);
		}

		std::cout << "Day1: increased measurements: " << GetIncreasedMeasurements(measurements) << std::endl;
		std::cout << "Day1: increased three measurements: " << GetIncreasedThreeMeasurements(measurements) << std::endl;
	}

	{
		std::vector<IntVector2> commands;

		{
			std::ifstream ifile("..\\Inputs\\Day2.txt");
			commands = LoadSubmarineCommandsStream(ifile);
		}

		std::cout << "Day2: commands count: " << commands.size() << std::endl;
	}
}
