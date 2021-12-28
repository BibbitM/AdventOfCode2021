#include <iostream>
#include <fstream>
#include <vector>

extern std::vector<int> LoadIntStream(std::istream& in);

int main()
{
	std::vector<int> inputData;
	{
		std::ifstream ifile("..\\Inputs\\Day1.txt");
		inputData = LoadIntStream(ifile);
	}

	std::cout << "Loaded " << inputData.size() << " elements." << std::endl;
}
