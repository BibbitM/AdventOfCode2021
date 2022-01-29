#include "../Code/BingoBoard.h"
#include "../Code/BingoCard.h"
#include "../Code/BingoNumbers.h"
#include "../Code/Cave.h"
#include "../Code/Cavern.h"
#include "../Code/DotsPaper.h"
#include "../Code/IntLine2.h"
#include "../Code/IntVector2.h"
#include "../Code/Heightmap.h"
#include "../Code/Lanternfish.h"
#include "../Code/NavigationSyntax.h"
#include "../Code/OctopusGrid.h"
#include "../Code/Polymerization.h"
#include "../Code/Transmission.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>

#define WRITE_OUTPUT_TO_README_FILE 1

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

constexpr const char c_outFileName[] = "..\\README.md";

#if WRITE_OUTPUT_TO_README_FILE
inline std::ostream& md_endl(std::ostream& out)
{
	out << "  " << std::endl;
	return out;
}
#else
#define md_endl std::endl
#endif

int main()
{
#if WRITE_OUTPUT_TO_README_FILE
	std::ofstream fout(c_outFileName);
	auto coutbuf = std::cout.rdbuf(fout.rdbuf());
#endif

	std::cout << "# AdventOfCode2021 results\n\n";

	{
		std::vector<int> measurements;

		{
			std::ifstream ifile("..\\Inputs\\Day1.txt");
			measurements = LoadIntStream(ifile);
		}

		std::cout << "Day1: increased measurements: " << GetIncreasedMeasurements(measurements) << md_endl;
		std::cout << "Day1: increased three measurements: " << GetIncreasedThreeMeasurements(measurements) << md_endl;
	}

	{
		std::vector<IntVector2> commands;

		{
			std::ifstream ifile("..\\Inputs\\Day2.txt");
			commands = LoadSubmarineCommandsStream(ifile);
		}

		std::cout << "Day2: multiplied position: " << GetSubmarineMultipliedPosition(commands) << md_endl;
		std::cout << "Day2: multiplied position with aim: " << GetSubmarineMultipliedPositionWithAim(commands) << md_endl;
	}

	{
		std::vector<int> numbers;

		{
			std::ifstream ifile("..\\Inputs\\Day3.txt");
			numbers = LoadBinaryStream(ifile);
		}

		std::cout << "Day3: power consumption: " << GetPowerConsumption(numbers, 12) << md_endl;
		std::cout << "Day3: life support rating: " << GetLifeSupportRating(numbers, 12) << md_endl;
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

		std::cout << "Day4: bingo score: " << cardOne.Play(numbers.AsVector()) << md_endl;
		std::cout << "Day4: last winner bingo score: " << cardTwo.PlayTillLast(numbers.AsVector()) << md_endl;
	}

	{
		std::vector<IntLine2> lines;

		{
			std::ifstream ifile("..\\Inputs\\Day5.txt");
			lines = LoadLinesStream(ifile);
		}

		std::cout << "Day5: dangerous points: " << CountDangerousPoints(lines) << md_endl;
		std::cout << "Day5: dangerous points with diagonal: " << CountDangerousPointsWithDiagonal(lines) << md_endl;
	}

	{
		LanternfishPopulation population;

		{
			std::ifstream ifile("..\\Inputs\\Day6.txt");
			ifile >> population;
		}

		population.Grow(80);
		std::cout << "Day6: population after 80 days: " << population.CountAll() << md_endl;
		population.Grow(256 - 80);
		std::cout << "Day6: population after 256 days: " << population.CountAll() << md_endl;
	}

	{
		std::vector<int> crabs;

		{
			std::ifstream ifile("..\\Inputs\\Day7.txt");
			crabs = LoadIntStream(ifile);
		}

		std::cout << "Day7: fuel cost: " << GetAlignFuelCost(crabs) << md_endl;
		std::cout << "Day7: real fuel cost: " << GetAlignRealFuelCost(crabs) << md_endl;
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

		std::cout << "Day7: 1478 digits count: " << count << md_endl;
		std::cout << "Day7: decoded output: " << output << md_endl;
	}

	{
		Heightmap heightmap;

		{
			std::ifstream ifile("..\\Inputs\\Day9.txt");
			ifile >> heightmap;
		}

		std::cout << "Day9: sum of risk level: " << heightmap.CalculateSumOfRiskLevel() << md_endl;

		std::vector<int> basins = heightmap.FindBasins();
		int top3BasinsMultiply = 1;
		for (size_t i = 0; i < std::min(basins.size(), 3ull); ++i)
			top3BasinsMultiply *= basins[i];

		std::cout << "Day9: top 3 basins multiply: " << top3BasinsMultiply << md_endl;
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

		std::cout << "Day10: total syntax error score: " << totalErrorScore << md_endl;
		std::cout << "Day10: middle completion score: " << middleCompletionScore << md_endl;
	}

	{
		OctopusGrid grid;

		{
			std::ifstream ifile("..\\Inputs\\Day11.txt");
			ifile >> grid;
		}

		grid.Step(100);
		std::cout << "Day11: total flashes after 100 steps: " << grid.GetFlashes() << md_endl;

		while (!grid.AllFlashed())
		{
			grid.Step();
		}
		std::cout << "Day11: all flashed in step: " << grid.GetSteps() << md_endl;
	}

	{
		CavesMap map;

		{
			std::ifstream ifile("..\\Inputs\\Day12.txt");
			ifile >> map;
		}

		std::cout << "Day12: unique paths: " << map.FindDistinctPathsCount() << md_endl;
		std::cout << "Day12: unique paths with double visit: " << map.FindDistinctPathsCount(true) << md_endl;
	}


	{
		DotsPaper paper;
		std::vector<Fold> folds;

		{
			std::ifstream ifile("..\\Inputs\\Day13.txt");
			ifile >> paper;
			ifile >> folds;
		}

		assert(!folds.empty());
		paper.FoldAlong(folds.front());
		std::cout << "Day13: dots after first fold: " << paper.CountDots() << md_endl;

		for (size_t i = 1u; i < folds.size(); ++i)
			paper.FoldAlong(folds[i]);
		std::cout << "Day13: paper after folds:" << md_endl;
		std::cout << "```\n" << paper << "```" << md_endl;
	}

	{
		Polimer polimer;
		std::vector<std::pair<PolimerPair, char>> instructions;

		{
			std::ifstream ifile("..\\Inputs\\Day14.txt");
			ifile >> polimer;
			ifile >> instructions;
		}

		for (int i = 0; i < 10; ++i)
			polimer.Grow(instructions);
		std::cout << "Day14: quantity max-min after 10 steps: " << polimer.CalculteMostSubLessQuantity() << md_endl;
		for (int i = 0; i < 30; ++i)
			polimer.Grow(instructions);
		std::cout << "Day14: quantity max-min after 40 steps: " << polimer.CalculteMostSubLessQuantity() << md_endl;
	}

	{
		Cavern cavern;

		{
			std::ifstream ifile("..\\Inputs\\Day15.txt");
			ifile >> cavern;
		}

		std::cout << "Day15: cavern total risk: " << cavern.CalculateRisk() << md_endl;

		cavern.Enlarge5x5();
		std::cout << "Day15: enlarged 5x5 cavern total risk: " << cavern.CalculateRisk() << md_endl;
	}

	{
		Transmission transmission;

		{
			std::ifstream ifile("..\\Inputs\\Day16.txt");
			ifile >> transmission;
		}

		std::cout << "Day16: sum of version numbers: " << ReadPacketVersion(transmission) << md_endl;
	}

#if WRITE_OUTPUT_TO_README_FILE
	std::cout.rdbuf(coutbuf);
	fout.close();

	std::ifstream fin(c_outFileName);
	std::cout << fin.rdbuf();
#endif
}
