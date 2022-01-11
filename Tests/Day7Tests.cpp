#include "pch.h"

#include <sstream>
#include <vector>

extern std::vector<int> LoadIntStream(std::istream& in);
extern int GetAlignFuelCost(const std::vector<int>& crabs);

namespace
{
	constexpr char c_exampleInput[] = "16,1,2,0,4,2,7,1,2,14";
	const std::vector<int> c_exampleNumbers({ 16, 1, 2, 0, 4, 2, 7, 1, 2, 14 });
}

TEST(Day7, LoadEmptyInput)
{
	std::istringstream input{};
	std::vector<int> numbers = LoadIntStream(input);
	EXPECT_TRUE(numbers.empty());
}

TEST(Day7, LoadComaSeparatedInput)
{
	std::istringstream input{ "1,2,3" };
	std::vector<int> numbers = LoadIntStream(input);
	EXPECT_EQ(numbers, std::vector<int>({ 1, 2, 3 }));
}

TEST(Day7, LoadExampleInput)
{
	std::istringstream input{ c_exampleInput };
	EXPECT_EQ(LoadIntStream(input), c_exampleNumbers);
}

TEST(Day7, GetAlignFuelCostForSingleCrab)
{
	std::vector<int> crabs({ 1 });
	EXPECT_EQ(GetAlignFuelCost(crabs), 0);
}

TEST(Day7, GetAlignFuelCostForLastToFirst)
{
	std::vector<int> crabs({ 1, 1, 2 });
	EXPECT_EQ(GetAlignFuelCost(crabs), 1);
}

TEST(Day7, GetAlignFuelCostForFirstToLast)
{
	std::vector<int> crabs({ 0, 10, 10, 10, 0 });
	EXPECT_EQ(GetAlignFuelCost(crabs), 20);
}

TEST(Day7, GetAlignFuelCostForExampleInput)
{
	EXPECT_EQ(GetAlignFuelCost(c_exampleNumbers), 37);
}
