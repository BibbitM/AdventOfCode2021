#include "pch.h"

#include <sstream>
#include <string>
#include <vector>

extern std::vector<int> LoadBinaryStream(std::istream& in);
extern int GetGammaRate(const std::vector<int>& numbers, int bits);
extern int GetEpsilonRate(const std::vector<int>& numbers, int bits);
extern int64_t GetPowerConsumption(const std::vector<int>& numbers, int bits);

namespace
{
	const std::vector<int> s_exampleNumbers({ 0b00100, 0b11110, 0b10110, 0b10111, 0b10101, 0b01111, 0b00111, 0b11100, 0b10000, 0b11001, 0b00010, 0b01010 });
}

TEST(Day3, LoadBinaryFromEmptyStream)
{
	std::stringstream emptyStream;

	std::vector<int> emptyVector = LoadBinaryStream(emptyStream);

	EXPECT_TRUE(emptyVector.empty());
}

TEST(Day3, LoadBinaryZero)
{
	std::stringstream stream( "000" );

	std::vector<int> numbers = LoadBinaryStream(stream);

	ASSERT_EQ(numbers.size(), 1);
	EXPECT_EQ(numbers[0], 0);
}

TEST(Day3, LoadBinaryNonZero)
{
	std::stringstream stream("0101");

	std::vector<int> numbers = LoadBinaryStream(stream);

	ASSERT_EQ(numbers.size(), 1);
	EXPECT_EQ(numbers[0], 5);
}

TEST(Day3, LoadBinaryMultipleValues)
{
	std::stringstream stream("0\n0101\n1111");

	std::vector<int> numbers = LoadBinaryStream(stream);

	EXPECT_EQ(numbers, std::vector<int>({ 0, 5, 15 }));
}

TEST(Day3, LoadBinaryExampleValues)
{
	std::stringstream stream(R"--(00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010
)--");

	std::vector<int> numbers = LoadBinaryStream(stream);

	EXPECT_EQ(numbers, std::vector<int>({ 4, 30, 22, 23, 21, 15, 7, 28, 16, 25, 2, 10 }));
	EXPECT_EQ(numbers, s_exampleNumbers);
}

TEST(Day3, GammaRateZero)
{
	EXPECT_EQ(GetGammaRate({ 0b0000 }, 4), 0b0000);
}

TEST(Day3, GammaRateOnes)
{
	EXPECT_EQ(GetGammaRate({ 0b111 }, 3), 0b111);
}

TEST(Day3, GammaRateExample)
{
	EXPECT_EQ(GetGammaRate(s_exampleNumbers, 5), 0b10110);
}

TEST(Day3, EpsilonRateOnes)
{
	EXPECT_EQ(GetEpsilonRate({ 0b111 }, 3), 0b000);
}

TEST(Day3, EpsilonRateZero)
{
	EXPECT_EQ(GetEpsilonRate({ 0b0000 }, 4), 0b1111);
}

TEST(Day3, EpsilonRateExample)
{
	EXPECT_EQ(GetEpsilonRate(s_exampleNumbers, 5), 0b01001);
}

TEST(Day3, PowerConsumptionZero)
{
	EXPECT_EQ(GetPowerConsumption({ 0b0000 }, 4), 0);
}

TEST(Day3, PowerConsumptionSimple)
{
	EXPECT_EQ(GetPowerConsumption({ 0b10, 0b10 }, 2), 2);
}

TEST(Day3, PowerConsumptionExample)
{
	EXPECT_EQ(GetPowerConsumption(s_exampleNumbers, 5), 198);
}
