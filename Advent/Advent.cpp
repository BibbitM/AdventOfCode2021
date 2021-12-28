#include <iostream>
#include <fstream>
#include <vector>

extern std::vector<int> LoadIntStream(std::istream& in);
extern int GetIncreasedMeasurements(std::vector<int> measurements);
extern int GetIncreasedThreeMeasurements(std::vector<int> measurements);

int main()
{
	std::vector<int> inputData;
	{
		std::ifstream ifile("..\\Inputs\\Day1.txt");
		inputData = LoadIntStream(ifile);
	}

	std::cout << "Increased measurements: " << GetIncreasedMeasurements(inputData) << std::endl;
	std::cout << "Increased three measurements: " << GetIncreasedThreeMeasurements(inputData) << std::endl;
}
