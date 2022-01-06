#include "../Code/BingoBoard.h"
#include "../Code/BingoCard.h"
#include "../Code/BingoNumbers.h"
#include "../Code/IntVector2.h"

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
}
