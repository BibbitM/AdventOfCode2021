#include "pch.h"

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

extern uint32_t GetBitsFromSignal(const std::string& signal);
extern std::istream& GetBitsAfterSeparator(std::istream& input, std::vector<uint32_t>& bits);
extern int CountNumbersWith2347Bits(const std::vector<uint32_t>& numbers);

namespace
{
	constexpr char c_exampleLine[] = "acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf";
	const std::vector<uint32_t> c_exampleBitsAfterSeparator({ 0b0111110u, 0b0101111u, 0b0111110u, 0b0101111u });
	constexpr char c_exampleInput[] = R"--(be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe
edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc
fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg
fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb
aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea
fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb
dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe
bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef
egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb
gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce)--";
}

TEST(Day8, GetBitsFromEmptySignal)
{
	EXPECT_EQ(GetBitsFromSignal(""), 0u);
}

TEST(Day8, GetBitsFromSimpleString)
{
	EXPECT_EQ(GetBitsFromSignal("a"), 0b00000001u);
}

TEST(Day8, GetBitsFromAnExample)
{
	EXPECT_EQ(GetBitsFromSignal("gacef"), 0b01110101u);
}

TEST(Day8, GetBitsVectorFromInputAfterSeparatorFromEmptyInput)
{
	std::istringstream input{};
	std::vector<uint32_t> numbers;
	GetBitsAfterSeparator(input, numbers);
	EXPECT_EQ(numbers, std::vector<uint32_t>());
}

TEST(Day8, GetBitsVectorFromInputAfterSeparatorFromSimpleString)
{
	std::istringstream input{ "a | b"};
	std::vector<uint32_t> numbers;
	GetBitsAfterSeparator(input, numbers);
	EXPECT_EQ(numbers, std::vector<uint32_t>({ 0b00000010u }));
}

TEST(Day8, GetBitsVectorFromInputAfterSeparatorFromExample)
{
	std::istringstream input{ c_exampleLine };
	std::vector<uint32_t> numbers;
	GetBitsAfterSeparator(input, numbers);
	EXPECT_EQ(numbers, c_exampleBitsAfterSeparator);
}

TEST(Day8, CountNumbersWith2347BitsZero)
{
	EXPECT_EQ(CountNumbersWith2347Bits(std::vector<uint32_t>({ 0u })), 0);
}

TEST(Day8, CountNumbersWith2347BitsSimple)
{
	EXPECT_EQ(CountNumbersWith2347Bits(std::vector<uint32_t>({ 0u, 0b0000010u, 0b0011100u, 0b11u, 0b010101010u, 0b1111111 })), 4);
}

TEST(Day8, CountNumbersWith2347BitsExample)
{
	EXPECT_EQ(CountNumbersWith2347Bits(c_exampleBitsAfterSeparator), 0);
}

TEST(Day8, CountNumbersWith2347BitsInTheWholeExampleImput)
{
	std::istringstream input(c_exampleInput);
	int count = 0;
	std::vector<uint32_t> numbers;
	while (GetBitsAfterSeparator(input, numbers))
	{
		count += CountNumbersWith2347Bits(numbers);
	}
	EXPECT_EQ(count, 26);
}
