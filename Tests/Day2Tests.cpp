#include "pch.h"

#include "../Code/IntVector2.h"
#include <sstream>
#include <vector>

extern std::vector<IntVector2> LoadSubmarineCommandsStream(std::istream& in);
extern int GetSubmarineMultipliedPosition(std::vector<IntVector2> commands);
TEST(Day2, IntVector2CreateEmpty)
{
	IntVector2 vec{};

	EXPECT_EQ(vec.x, 0);
	EXPECT_EQ(vec.y, 0);
}

TEST(Day2, IntVector2CreateXY)
{
	IntVector2 vec{ 10, 20 };

	EXPECT_EQ(vec.x, 10);
	EXPECT_EQ(vec.y, 20);
}

TEST(Day2, IntVector2Equals)
{
	IntVector2 vec{ 1, 2 };
	IntVector2 vecEq = vec;
	IntVector2 vecNe{ 2, 1 };

	EXPECT_EQ(vec, vecEq);
	EXPECT_NE(vec, vecNe);
}

TEST(Day2, IntVector2AccumulateZeros)
{
	constexpr IntVector2 zero{};

	IntVector2 vec = zero;

	EXPECT_EQ(vec += zero, zero);
}

TEST(Day2, IntVector2AccumulateValues)
{
	IntVector2 vec(1, 2);
	EXPECT_EQ(vec += IntVector2(10, 20), IntVector2(11, 22));
}

TEST(Day2, LoadFromEmptyStream)
{
	std::stringstream emptyStream;

	std::vector<IntVector2> emptyVector = LoadSubmarineCommandsStream(emptyStream);

	EXPECT_TRUE(emptyVector.empty());
}

TEST(Day2, LoadForwardFromStream)
{
	std::stringstream stream("forward 10");

	std::vector<IntVector2> commands = LoadSubmarineCommandsStream(stream);

	ASSERT_EQ(commands.size(), 1);
	EXPECT_EQ(commands[0], IntVector2(10, 0));
}

TEST(Day2, LoadDownFromStream)
{
	std::stringstream stream("down 100");

	std::vector<IntVector2> commands = LoadSubmarineCommandsStream(stream);

	ASSERT_EQ(commands.size(), 1);
	EXPECT_EQ(commands[0], IntVector2(0, 100));
}

TEST(Day2, LoadUpFromStream)
{
	std::stringstream stream("up 1");

	std::vector<IntVector2> commands = LoadSubmarineCommandsStream(stream);

	ASSERT_EQ(commands.size(), 1);
	EXPECT_EQ(commands[0], IntVector2(0, -1));
}

TEST(Day2, LoadMultipleCommandsStream)
{
	std::stringstream stream{ R"--(down 10
up 5
forward 10
forward 1
)--" };

	std::vector<IntVector2> commands = LoadSubmarineCommandsStream(stream);

	EXPECT_EQ(commands, std::vector<IntVector2>({ { 0, 10 }, { 0, -5 }, { 10, 0 }, { 1, 0 } }));
}

TEST(Day2, LoadExampleCommandsStream)
{
	std::stringstream stream{ R"--(forward 5
down 5
forward 8
up 3
down 8
forward 2)--" };

	std::vector<IntVector2> commands = LoadSubmarineCommandsStream(stream);

	EXPECT_EQ(commands, std::vector<IntVector2>({ { 5, 0 }, { 0, 5 }, { 8, 0 }, { 0, -3 }, { 0, 8 }, { 2, 0 } }));
}

TEST(Day2, SubmarineMultipliedPositionEmptyCommands)
{
	EXPECT_EQ(GetSubmarineMultipliedPosition({}), 0);
}

TEST(Day2, SubmarineMultipliedPositionSingleCommand)
{
	EXPECT_EQ(GetSubmarineMultipliedPosition({ { 3, 4 } }), 12);
}

TEST(Day2, SubmarineMultipliedPositionNegativeCommand)
{
	EXPECT_EQ(GetSubmarineMultipliedPosition({ { 1, -2 } }), 2);
}

TEST(Day2, SubmarineMultipiedPositionExampleCommands)
{
	EXPECT_EQ(GetSubmarineMultipliedPosition({ { 5, 0 }, { 0, 5 }, { 8, 0 }, { 0, -3 }, { 0, 8 }, { 2, 0 } }), 150);
}
