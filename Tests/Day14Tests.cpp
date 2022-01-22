#include "pch.h"

#include "../Code/Polymerization.h"

#include <string>

namespace
{
	constexpr const char c_exampleInput[] = R"--(NNCB

CH -> B
HH -> N
CB -> H
NH -> C
HB -> C
HC -> B
HN -> C
NN -> C
BH -> H
NC -> B
NB -> B
BN -> B
BB -> N
BC -> B
CC -> N
CN -> C)--";

	constexpr const char c_examplePolimer[] = "NNCB";
}

TEST(Day14, PolimerGrowEmpty)
{
	Polimer polimer;
	polimer.Grow(std::vector<std::pair<std::string, char>>({ { "AB", 'A' } }));
	EXPECT_EQ(polimer.AsString(), "");
}

TEST(Day14, PolimerGrowInsertsElementBetween)
{
	Polimer polimer("AB");
	polimer.Grow(std::vector<std::pair<std::string, char>>({ { "AB", 'C' } }));
	EXPECT_EQ(polimer.AsString(), "ACB");
}

TEST(Day14, PolimerGrowInsertElemetnForAllMaching)
{
	Polimer polimer("XZXZ");
	polimer.Grow(std::vector<std::pair<std::string, char>>({ { "XZ", 'Y' } }));
	EXPECT_EQ(polimer.AsString(), "XYZXYZ");
}

TEST(Day14, PolimerGrowChecksMultipleInstructions)
{
	Polimer polimer("ABCD");
	polimer.Grow(std::vector<std::pair<std::string, char>>({ { "XZ", 'Y' }, { "AB", 'E' }, { "BC", 'F' }}));
	EXPECT_EQ(polimer.AsString(), "AEBFCD");
}

TEST(Day14, PolimerGrowIgnoresInserted)
{
	Polimer polimer("AB");
	polimer.Grow(std::vector<std::pair<std::string, char>>({ { "AB", 'C' }, { "AC", 'D' } }));
	EXPECT_EQ(polimer.AsString(), "ACB");
}

TEST(Day14, PolimerSubQuantityMostLess)
{
	Polimer polimer("ABACBBB");
	EXPECT_EQ(polimer.CalculteMostSubLessQuantity(), 3);
}

TEST(Day14, PolimerExampleInput)
{
	Polimer polimer;
	std::istringstream input(c_exampleInput);

	input >> polimer;

	EXPECT_EQ(polimer.AsString(), c_examplePolimer);

	std::vector<std::pair<std::string, char>> instructions;

	input >> instructions;

	ASSERT_EQ(instructions.size(), 16);
	EXPECT_EQ(instructions.front(), (std::pair<std::string, char>("CH", 'B')));
	EXPECT_EQ(instructions.back(), (std::pair<std::string, char>("CN", 'C')));

	polimer.Grow(instructions);
	EXPECT_EQ(polimer.AsString(), "NCNBCHB");
	polimer.Grow(instructions);
	EXPECT_EQ(polimer.AsString(), "NBCCNBBBCBHCB");
	polimer.Grow(instructions);
	EXPECT_EQ(polimer.AsString(), "NBBBCNCCNBBNBNBBCHBHHBCHB");
	polimer.Grow(instructions);
	EXPECT_EQ(polimer.AsString(), "NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB");
	polimer.Grow(instructions);
	EXPECT_EQ(polimer.GetLength(), 97);
	for (int i = 0; i < 5; ++i)
		polimer.Grow(instructions);
	EXPECT_EQ(polimer.GetLength(), 3073);
	EXPECT_EQ(polimer.CalculteMostSubLessQuantity(), 1588);
}
