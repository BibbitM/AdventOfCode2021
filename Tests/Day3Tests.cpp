#include "pch.h"

#include <sstream>
#include <string>
#include <vector>

extern std::vector<int> LoadBinaryStream(std::istream& in);

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
	EXPECT_EQ(numbers, std::vector<int>({ 0b00100, 0b11110, 0b10110, 0b10111, 0b10101, 0b01111, 0b00111, 0b11100, 0b10000, 0b11001, 0b00010, 0b01010 }));
}
