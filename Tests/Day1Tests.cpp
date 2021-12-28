#include "pch.h"

#include <sstream>
#include <string>
#include <vector>

extern std::vector<int> LoadIntStream(std::istream& in);
extern int GetIncreasedMeasurements(std::vector<int> measurements);

TEST(Day1, LoadFromEmptyStream)
{
	std::stringstream emptyStream;

	std::vector<int> emptyVector = LoadIntStream(emptyStream);

	EXPECT_TRUE(emptyVector.empty());
}

TEST(Day1, LoadSingleValueFromStream)
{
	std::stringstream singleValueStream{ "0" };

	std::vector<int> singleValueVector = LoadIntStream(singleValueStream);

	ASSERT_EQ(singleValueVector.size(), 1);
	EXPECT_EQ(singleValueVector[0], 0);
}

TEST(Day1, LoadMultipleValuesFromStream)
{
	std::stringstream valueStream{ R"--(1
2
3)--" };

	std::vector<int> valueVector = LoadIntStream(valueStream);

	EXPECT_EQ(valueVector.size(), 3);
	EXPECT_EQ(valueVector, std::vector<int>({ 1, 2, 3 }));
}

TEST(Day1, LoadExampleDataFromStream)
{
	std::stringstream valueStream{ R"--(199
200
208
210
200
207
240
269
260
263)--" };

	std::vector<int> valueVector = LoadIntStream(valueStream);

	EXPECT_EQ(valueVector, std::vector<int>({ 199, 200, 208, 210, 200, 207, 240, 269, 260, 263 }));
}

TEST(Day1, LoadEmptyLineThrows)
{
	std::stringstream valueStream{ "  " };

	EXPECT_THROW(LoadIntStream(valueStream), std::invalid_argument);
}

TEST(Day1, LoadNotANumberThrows)
{
	std::stringstream valueStream{ "1\ntext\2" };

	EXPECT_THROW(LoadIntStream(valueStream), std::invalid_argument);
}

TEST(Day1, EmptyMeasurementsReturnsZero)
{
	std::vector<int> emptyMeasurement;

	EXPECT_EQ(GetIncreasedMeasurements(emptyMeasurement), 0);
}

TEST(Day1, SingleMeasurementsReturnsZero)
{
	std::vector<int> singleMeasurement{ 100 };

	EXPECT_EQ(GetIncreasedMeasurements(singleMeasurement), 0);
}

TEST(Day1, IncreasingMeasurementsReturnsOne)
{
	std::vector<int> measurements{ 100, 101 };

	EXPECT_EQ(GetIncreasedMeasurements(measurements), 1);
}

TEST(Day1, ConstMeasurementsReturnsZero)
{
	std::vector<int> measurements{ 1000, 1000 };

	EXPECT_EQ(GetIncreasedMeasurements(measurements), 0);
}

TEST(Day1, DecreasingMeasurementsReturnsZero)
{
	std::vector<int> measurements{ 200, 1 };

	EXPECT_EQ(GetIncreasedMeasurements(measurements), 0);
}

TEST(Day1, SimpleMeasurementsReturnsThree)
{
	std::vector<int> measurements{ 100, 101, 0, 0, 1, 2 };

	EXPECT_EQ(GetIncreasedMeasurements(measurements), 3);
}

TEST(Day1, ExampleMeasurementReturnsSeven)
{
	std::vector<int> measurements{ 199, 200, 208, 210, 200, 207, 240, 269, 260, 263 };

	EXPECT_EQ(GetIncreasedMeasurements(measurements), 7);
}
