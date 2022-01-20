#include "../Code/BingoBoard.h"
#include "../Code/BingoCard.h"
#include "../Code/BingoNumbers.h"
#include "../Code/IntLine2.h"
#include "../Code/IntVector2.h"
#include "../Code/Heightmap.h"
#include "../Code/Lanternfish.h"
#include "../Code/NavigationSyntax.h"
#include "../Code/OctopusGrid.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

extern std::vector<int> LoadIntStream(std::istream& in);
extern int GetIncreasedMeasurements(const std::vector<int>& measurements);
extern int GetIncreasedThreeMeasurements(const std::vector<int>& measurements);

extern std::vector<IntVector2> LoadSubmarineCommandsStream(std::istream& in);
extern int GetSubmarineMultipliedPosition(const std::vector<IntVector2>& commands);
extern int64_t GetSubmarineMultipliedPositionWithAim(const std::vector<IntVector2>& commands);

extern std::vector<int> LoadBinaryStream(std::istream& in);
extern int64_t GetPowerConsumption(const std::vector<int>& numbers, int bits);
extern int64_t GetLifeSupportRating(const std::vector<int>& numbers, int bits);

extern std::vector<IntLine2> LoadLinesStream(std::istream& in);
extern int CountDangerousPoints(const std::vector<IntLine2>& lines);
extern int CountDangerousPointsWithDiagonal(const std::vector<IntLine2>& lines);

extern int GetAlignFuelCost(const std::vector<int>& crabs);
extern int GetAlignRealFuelCost(const std::vector<int>& crabs);

extern std::istream& GetBitsCodeAndMessage(std::istream& input, std::vector<uint32_t>& code, std::vector<uint32_t>& message);
extern int CountNumbersWith2347Bits(const std::vector<uint32_t>& numbers);
extern std::array<uint32_t, 10> CreateDecoderFromTestSignal(const std::vector<uint32_t>& code);
extern uint32_t DecodeMessage(const std::array<uint32_t, 10>& decoder, const std::vector<uint32_t>& message);


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

		std::cout << "Day2: multiplied position: " << GetSubmarineMultipliedPosition(commands) << std::endl;
		std::cout << "Day2: multiplied position with aim: " << GetSubmarineMultipliedPositionWithAim(commands) << std::endl;
	}

	{
		std::vector<int> numbers;

		{
			std::ifstream ifile("..\\Inputs\\Day3.txt");
			numbers = LoadBinaryStream(ifile);
		}

		std::cout << "Day3: power consumption: " << GetPowerConsumption(numbers, 12) << std::endl;
		std::cout << "Day3: life support rating: " << GetLifeSupportRating(numbers, 12) << std::endl;
	}

	{
		BingoNumbers numbers;
		BingoCard cardOne;
		BingoCard cardTwo;

		{
			std::ifstream ifile("..\\Inputs\\Day4.txt");
			ifile >> numbers;

			for (BingoBoard board; ifile >> board; )
			{
				cardOne.AddBoard(board);
				cardTwo.AddBoard(board);
			}
		}

		std::cout << "Day4: bingo score: " << cardOne.Play(numbers.AsVector()) << std::endl;
		std::cout << "Day4: last winner bingo score: " << cardTwo.PlayTillLast(numbers.AsVector()) << std::endl;
	}

	{
		std::vector<IntLine2> lines;

		{
			std::ifstream ifile("..\\Inputs\\Day5.txt");
			lines = LoadLinesStream(ifile);
		}

		std::cout << "Day5: dangerous points: " << CountDangerousPoints(lines) << std::endl;
		std::cout << "Day5: dangerous points with diagonal: " << CountDangerousPointsWithDiagonal(lines) << std::endl;
	}

	{
		LanternfishPopulation population;

		{
			std::ifstream ifile("..\\Inputs\\Day6.txt");
			ifile >> population;
		}

		population.Grow(80);
		std::cout << "Day6: population after 80 days: " << population.CountAll() << std::endl;
		population.Grow(256 - 80);
		std::cout << "Day6: population after 256 days: " << population.CountAll() << std::endl;
	}

	{
		std::vector<int> crabs;

		{
			std::ifstream ifile("..\\Inputs\\Day7.txt");
			crabs = LoadIntStream(ifile);
		}

		std::cout << "Day7: fuel cost: " << GetAlignFuelCost(crabs) << std::endl;
		std::cout << "Day7: real fuel cost: " << GetAlignRealFuelCost(crabs) << std::endl;
	}

	{
		int count = 0;
		uint32_t output = 0u;

		{
			std::ifstream ifile("..\\Inputs\\Day8.txt");
			std::vector<uint32_t> code;
			std::vector<uint32_t> message;
			while (GetBitsCodeAndMessage(ifile, code, message))
			{
				count += CountNumbersWith2347Bits(message);
				output += DecodeMessage(CreateDecoderFromTestSignal(code), message);
			}
		}

		std::cout << "Day7: 1478 digits count: " << count << std::endl;
		std::cout << "Day7: decoded output: " << output << std::endl;
	}

	{
		Heightmap heightmap;

		{
			std::ifstream ifile("..\\Inputs\\Day9.txt");
			ifile >> heightmap;
		}

		std::cout << "Day9: sum of risk level: " << heightmap.CalculateSumOfRiskLevel() << std::endl;

		std::vector<int> basins = heightmap.FindBasins();
		int top3BasinsMultiply = 1;
		for (size_t i = 0; i < std::min(basins.size(), 3ull); ++i)
			top3BasinsMultiply *= basins[i];

		std::cout << "Day9: top 3 basins multiply: " << top3BasinsMultiply << std::endl;
	}

	{
		int totalErrorScore = 0;
		int64_t middleCompletionScore = 0;
		std::vector<int64_t> completionScores;

		{
			std::ifstream ifile("..\\Inputs\\Day10.txt");

			std::string line;
			while (std::getline(ifile, line))
			{
				totalErrorScore += NavigationSyntax::GetErrorScore(NavigationSyntax::FindChunkError(line));
				std::string completionLine = NavigationSyntax::DetermineLineCompletion(line);
				if (!completionLine.empty())
					completionScores.push_back(NavigationSyntax::GetCompletionScore(completionLine));
			}
		}

		if (!completionScores.empty())
		{
			std::sort(completionScores.begin(), completionScores.end());
			middleCompletionScore = completionScores[completionScores.size() / 2];
		}

		std::cout << "Day10: total syntax error score: " << totalErrorScore << std::endl;
		std::cout << "Day10: middle completion score: " << middleCompletionScore << std::endl;
	}

	{
		OctopusGrid grid;

		{
			std::ifstream ifile("..\\Inputs\\Day11.txt");
			ifile >> grid;
		}

		grid.Step(100);
		std::cout << "Day11: total flashes after 100 steps: " << grid.GetFlashes() << std::endl;

		while (!grid.AllFlashed())
		{
			grid.Step();
		}
		std::cout << "Day11: all flashed in step: " << grid.GetSteps() << std::endl;
	}
}
