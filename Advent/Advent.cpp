#include "../Code/Amphipods.h"
#include "../Code/BingoBoard.h"
#include "../Code/BingoCard.h"
#include "../Code/BingoNumbers.h"
#include "../Code/Cave.h"
#include "../Code/Cavern.h"
#include "../Code/Cube.h"
#include "../Code/DiracDice.h"
#include "../Code/DotsPaper.h"
#include "../Code/IntLine2.h"
#include "../Code/IntVector2.h"
#include "../Code/Heightmap.h"
#include "../Code/Lanternfish.h"
#include "../Code/NavigationSyntax.h"
#include "../Code/OctopusGrid.h"
#include "../Code/Polymerization.h"
#include "../Code/Scanner.h"
#include "../Code/ScannerImage.h"
#include "../Code/SnailfishNumber.h"
#include "../Code/Timer.h"
#include "../Code/Transmission.h"
#include "../Code/TrickShot.h"

#include <algorithm>
#include <cassert>
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

constexpr const char c_outFileName[] = "..\\README.md";

inline std::ostream& md_endl(std::ostream& out)
{
	out << "  \n";
	return out;
}

int main()
{
	std::cout << "# AdventOfCode2021 results\n\n";

	{
		SCOPE_TIMER("Day1");
		std::vector<int> measurements;

		{
			std::ifstream ifile("..\\Inputs\\Day1.txt");
			measurements = LoadIntStream(ifile);
		}

		std::cout << "Day1: increased measurements: " << GetIncreasedMeasurements(measurements) << md_endl;
		std::cout << "Day1: increased three measurements: " << GetIncreasedThreeMeasurements(measurements) << md_endl;
	}

	{
		SCOPE_TIMER("Day2");
		std::vector<IntVector2> commands;

		{
			std::ifstream ifile("..\\Inputs\\Day2.txt");
			commands = LoadSubmarineCommandsStream(ifile);
		}

		std::cout << "Day2: multiplied position: " << GetSubmarineMultipliedPosition(commands) << md_endl;
		std::cout << "Day2: multiplied position with aim: " << GetSubmarineMultipliedPositionWithAim(commands) << md_endl;
	}

	{
		SCOPE_TIMER("Day3");
		std::vector<int> numbers;

		{
			std::ifstream ifile("..\\Inputs\\Day3.txt");
			numbers = LoadBinaryStream(ifile);
		}

		std::cout << "Day3: power consumption: " << GetPowerConsumption(numbers, 12) << md_endl;
		std::cout << "Day3: life support rating: " << GetLifeSupportRating(numbers, 12) << md_endl;
	}

	{
		SCOPE_TIMER("Day4");
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
		SCOPE_TIMER("Day5");
		std::vector<IntLine2> lines;

		{
			std::ifstream ifile("..\\Inputs\\Day5.txt");
			lines = LoadLinesStream(ifile);
		}

		std::cout << "Day5: dangerous points: " << CountDangerousPoints(lines) << md_endl;
		std::cout << "Day5: dangerous points with diagonal: " << CountDangerousPointsWithDiagonal(lines) << md_endl;
	}

	{
		SCOPE_TIMER("Day6");
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
		SCOPE_TIMER("Day7");
		std::vector<int> crabs;

		{
			std::ifstream ifile("..\\Inputs\\Day7.txt");
			crabs = LoadIntStream(ifile);
		}

		std::cout << "Day7: fuel cost: " << GetAlignFuelCost(crabs) << md_endl;
		std::cout << "Day7: real fuel cost: " << GetAlignRealFuelCost(crabs) << md_endl;
	}

	{
		SCOPE_TIMER("Day8");
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

		std::cout << "Day8: 1478 digits count: " << count << md_endl;
		std::cout << "Day8: decoded output: " << output << md_endl;
	}

	{
		SCOPE_TIMER("Day9");
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
		SCOPE_TIMER("Day10");
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
		SCOPE_TIMER("Day11");
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
		SCOPE_TIMER("Day12");
		CavesMap map;

		{
			std::ifstream ifile("..\\Inputs\\Day12.txt");
			ifile >> map;
		}

		std::cout << "Day12: unique paths: " << map.FindDistinctPathsCount() << md_endl;
		std::cout << "Day12: unique paths with double visit: " << map.FindDistinctPathsCount(true) << md_endl;
	}


	{
		SCOPE_TIMER("Day13");
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
		SCOPE_TIMER("Day14");
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
		SCOPE_TIMER("Day15");
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
		SCOPE_TIMER("Day16");
		Transmission transmission;

		{
			std::ifstream ifile("..\\Inputs\\Day16.txt");
			ifile >> transmission;
		}

		std::cout << "Day16: sum of version numbers: " << ReadPacketVersion(transmission) << md_endl;
		transmission.Reset();
		std::cout << "Day16: value of evaluated expression: " << ReadPacketValue(transmission) << md_endl;
	}

	{
		SCOPE_TIMER("Day17");
		TrickShot::TargetArea area;

		{
			std::ifstream ifile("..\\Inputs\\Day17.txt");
			ifile >> area;
		}

		std::vector<IntVector2> allShots = TrickShot::FindAllShots(area);
		int highestShot = !allShots.empty() ? allShots.back().y : 0;
		std::cout << "Day17: maximum y position: " << TrickShot::GetHighestPosition(highestShot) << md_endl;
		std::cout << "Day17: count of distinct initial velocity: " << allShots.size() << md_endl;
	}

	{
		SCOPE_TIMER("Day18");
		std::vector<std::string> lines;

		{
			std::ifstream ifile("..\\Inputs\\Day18.txt");
			std::string line;
			while (std::getline(ifile, line))
				lines.push_back(std::move(line));
		}

		Snailfish::Number sum;
		if (!lines.empty())
			sum = Snailfish::Number(lines.front());
		for (size_t i = 1; i < lines.size(); ++i)
			sum = sum + Snailfish::Number(lines[i]);

		int largestMagnitude = 0;
		for (size_t x = 0; x < lines.size(); ++x)
		{
			for (size_t y = 0; y < lines.size(); ++y)
			{
				if (x == y)
					continue;

				Snailfish::Number xNum(lines[x]);
				Snailfish::Number yNum(lines[y]);

				{
					const int magnitude = (xNum + yNum).Magnitude();
					if (magnitude > largestMagnitude)
						largestMagnitude = magnitude;
				}

				{
					const int magnitude = (yNum + xNum).Magnitude();
					if (magnitude > largestMagnitude)
						largestMagnitude = magnitude;
				}
			}
		}

		std::cout << "Day18: the magnitude of the final sum: " << sum.Magnitude() << md_endl;
		std::cout << "Day18: the largest magnitude of any sum: " << largestMagnitude << md_endl;
	}

	{
		SCOPE_TIMER("Day19");
		std::vector<Scanner> unalignedScanners;
		constexpr size_t c_numOverlappingBeacons = 12;

		{
			std::ifstream ifile("..\\Inputs\\Day19.txt");

			while (ifile)
			{
				auto& scanner = unalignedScanners.emplace_back();
				ifile >> scanner;
			}
		}

		assert(!unalignedScanners.empty());

		std::vector<Scanner> allignedScanners;
		std::vector<Scanner> candidateScanners;
		allignedScanners.reserve(unalignedScanners.size());
		candidateScanners.reserve(unalignedScanners.size());

		candidateScanners.push_back(std::move(unalignedScanners.back()));
		unalignedScanners.pop_back();

		while (!candidateScanners.empty() && !unalignedScanners.empty())
		{
			Scanner candidate(std::move(candidateScanners.back()));
			candidateScanners.pop_back();

			for (auto it = unalignedScanners.begin(); it != unalignedScanners.end(); /*in loop*/)
			{
				if (it->OverlapWith(candidate, c_numOverlappingBeacons))
				{
					candidateScanners.push_back(std::move(*it));
					it = unalignedScanners.erase(it);
				}
				else
					++it;
			}

			allignedScanners.push_back(std::move(candidate));
		}
		assert(unalignedScanners.empty());

		allignedScanners.insert(
			allignedScanners.end(),
			std::make_move_iterator(candidateScanners.begin()),
			std::make_move_iterator(candidateScanners.end()));
		candidateScanners.clear();

		for (size_t i = 1; i < allignedScanners.size(); ++i)
		{
			allignedScanners[0].Merge(allignedScanners[i]);
		}

		std::cout << "Day19: number of beacons: " << allignedScanners[0].BeaconsCount() << md_endl;

		int maxDistance = 0;

		for (size_t i = 0; i + 1 < allignedScanners.size(); ++i)
		{
			for (size_t j = i + 1; j < allignedScanners.size(); ++j)
			{
				const int distance = ManhattanDistance(allignedScanners[i].GetOffset(), allignedScanners[j].GetOffset());
				if (distance > maxDistance)
					maxDistance = distance;
			}
		}

		std::cout << "Day19: the largest Manhattan distance: " << maxDistance << md_endl;
	}

	{
		SCOPE_TIMER("Day20");
		ScannerImage image;
		std::vector<bool> enhacementAlgorithm;

		{
			std::ifstream ifile("..\\Inputs\\Day20.txt");

			std::string enhancementLine;
			if (std::getline(ifile, enhancementLine))
				AppendBoolVectorByString(enhacementAlgorithm, enhancementLine);

			ifile.ignore(); //< Skip line

			ifile >> image;
		}

		ScannerImage enhancedImage = image.Enhance(enhacementAlgorithm);
		ScannerImage enhancedImageTwice = enhancedImage.Enhance(enhacementAlgorithm);
		std::cout << "Day20: lit pixels in the resulting image (x2): " << enhancedImageTwice.CountLitPixels() << md_endl;

		for (size_t i = 0; i < 50; ++i)
			image = image.Enhance(enhacementAlgorithm);
		std::cout << "Day20: lit pixels in the resulting image (x50): " << image.CountLitPixels() << md_endl;
	}


	{
		SCOPE_TIMER("Day21");
		Dirac::Game game;

		{
			std::ifstream ifile("..\\Inputs\\Day21.txt");

			ifile >> game;
		}

		Dirac::Game quantumGame{ game };

		int gameScore = game.Play();
		uint64_t quantumGameWinningUniverses = quantumGame.PlayQuantum(21);

		std::cout << "Day21: the game score: " << gameScore << md_endl;
		std::cout << "Day21: the game universes in which player wins: " << quantumGameWinningUniverses << md_endl;
	}

	{
		SCOPE_TIMER("Day22");
		CubeMap map;
		CubeMap mapLimited;

		{
			std::ifstream ifile("..\\Inputs\\Day22.txt");

			std::string op;
			Cube cube;

			constexpr Cube region({ -50, -50, -50 }, { 50, 50, 50 });
			while (ifile >> op >> cube)
			{
				if (op == "on")
					map.On(cube);
				else if (op == "off")
					map.Off(cube);
				else
					assert(false);

				if (region.Intersection(cube) != cube)
					continue;

				if (op == "on")
					mapLimited.On(cube);
				else if (op == "off")
					mapLimited.Off(cube);
				else
					assert(false);
			}
		}

		std::cout << "Day22: cubes on in -50..50 region: " << mapLimited.Volume() << md_endl;
		std::cout << "Day22: cubes on: " << map.Volume() << md_endl;
	}

	{
		SCOPE_TIMER("Day23");
		Amphipods::Burrow burrow;
		CubeMap mapLimited;

		{
			std::ifstream ifile("..\\Inputs\\Day23.txt");

			ifile >> burrow;
			}

		std::cout << "Day22: the least energy required to organize the amphipods: " << burrow.CalculateOrganizationCost() << md_endl;
		burrow.Unfold();
		std::cout << "Day22: the least energy required to organize the full diagram: " << burrow.CalculateOrganizationCost() << md_endl;
	}
}
