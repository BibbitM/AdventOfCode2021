#include "pch.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>
#include <sstream>
#include <string>
#include <vector>

extern uint32_t GetBitsFromSignal(const std::string& signal);
extern std::istream& GetBitsCodeAndMessage(std::istream& input, std::vector<uint32_t>& code, std::vector<uint32_t>& message);
extern int CountNumbersWith2347Bits(const std::vector<uint32_t>& numbers);
extern std::array<uint32_t, 10> CreateDecoderFromTestSignal(const std::vector<uint32_t>& code);
extern uint32_t DecodeMessage(const std::array<uint32_t, 10>& decoder, const std::vector<uint32_t>& message);


namespace
{
	constexpr char c_exampleLine[] = "acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf";
	//                                                           gfedcba      fedcb      gf dc a      f dcba        d ba      fedcba     gfedcb       fe  ba     g edcba          ba
	const std::vector<uint32_t> c_exampleBitsBeforeSeparator({ 0b1111111u, 0b0111110u, 0b1101101u, 0b0101111u, 0b0001011u, 0b0111111u, 0b1111110u, 0b0110011u, 0b1011111u, 0b0000011u });
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

	//   0:      1:      2:      3:      4:
	//  aaaa    ....    aaaa    aaaa    ....
	// b    c  .    c  .    c  .    c  b    c
	// b    c  .    c  .    c  .    c  b    c
	//  ....    ....    dddd    dddd    dddd
	// e    f  .    f  e    .  .    f  .    f
	// e    f  .    f  e    .  .    f  .    f
	//  gggg    ....    gggg    gggg    ....
	// 
	//   5:      6:      7:      8:      9:
	//  aaaa    aaaa    aaaa    aaaa    aaaa
	// b    .  b    .  .    c  b    c  b    c
	// b    .  b    .  .    c  b    c  b    c
	//  dddd    dddd    ....    dddd    dddd
	// .    f  e    f  .    f  e    f  .    f
	// .    f  e    f  .    f  e    f  .    f
	//  gggg    gggg    ....    gggg    gggg
	const uint32_t c_defaultNumbersBits[] = {
		GetBitsFromSignal("abcefg"),
		GetBitsFromSignal("cf"),
		GetBitsFromSignal("acdeg"),
		GetBitsFromSignal("acdfg"),
		GetBitsFromSignal("bcdf"),
		GetBitsFromSignal("abdfg"),
		GetBitsFromSignal("abdefg"),
		GetBitsFromSignal("acf"),
		GetBitsFromSignal("abcdefg"),
		GetBitsFromSignal("abcdfg"),
	};
	static_assert(std::size(c_defaultNumbersBits) == 10, "Default numbers contains 10 numbers");
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

TEST(Day8, GetBitsCodeAndMessageFromEmptyInput)
{
	std::istringstream input{};
	std::vector<uint32_t> code;
	std::vector<uint32_t> message;
	GetBitsCodeAndMessage(input, code, message);
	EXPECT_EQ(code, std::vector<uint32_t>());
	EXPECT_EQ(message, std::vector<uint32_t>());
}

TEST(Day8, GetBitsCodeAndMessageFromSimpleString)
{
	std::istringstream input{ "a | b" };
	std::vector<uint32_t> code;
	std::vector<uint32_t> message;
	GetBitsCodeAndMessage(input, code, message);
	EXPECT_EQ(code, std::vector<uint32_t>({ 0b00000001u }));
	EXPECT_EQ(message, std::vector<uint32_t>({ 0b00000010u }));
}

TEST(Day8, GetBitsCodeAndMessageFromExample)
{
	std::istringstream input{ c_exampleLine };
	std::vector<uint32_t> code;
	std::vector<uint32_t> message;
	GetBitsCodeAndMessage(input, code, message);
	EXPECT_EQ(code, c_exampleBitsBeforeSeparator);
	EXPECT_EQ(message, c_exampleBitsAfterSeparator);
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
	std::vector<uint32_t> code;
	std::vector<uint32_t> message;
	while (GetBitsCodeAndMessage(input, code, message))
	{
		count += CountNumbersWith2347Bits(message);
	}
	EXPECT_EQ(count, 26);
}

TEST(Day8, CreateDecoderBasedOnDefaultTestSignal)
{
	std::vector<uint32_t> code(std::begin(c_defaultNumbersBits), std::end(c_defaultNumbersBits));
	auto rng = std::default_random_engine{};
	std::shuffle(code.begin(), code.end(), rng);
	std::array<uint32_t, 10> decoder = CreateDecoderFromTestSignal(code);

	// Simple numbers
	EXPECT_EQ(decoder[1], c_defaultNumbersBits[1]);
	EXPECT_EQ(decoder[4], c_defaultNumbersBits[4]);
	EXPECT_EQ(decoder[7], c_defaultNumbersBits[7]);
	EXPECT_EQ(decoder[8], c_defaultNumbersBits[8]);

	// 6 bits numbers
	EXPECT_EQ(decoder[0], c_defaultNumbersBits[0]);
	EXPECT_EQ(decoder[6], c_defaultNumbersBits[6]);
	EXPECT_EQ(decoder[9], c_defaultNumbersBits[9]);

	// 5 bits numbers
	EXPECT_EQ(decoder[2], c_defaultNumbersBits[2]);
	EXPECT_EQ(decoder[3], c_defaultNumbersBits[3]);
	EXPECT_EQ(decoder[5], c_defaultNumbersBits[5]);
}

TEST(Day8, DecodeShortMessage)
{
	std::array<uint32_t, 10> decoder = CreateDecoderFromTestSignal(std::vector<uint32_t>(std::begin(c_defaultNumbersBits), std::end(c_defaultNumbersBits)));

	EXPECT_EQ(DecodeMessage(decoder, std::vector<uint32_t>({ c_defaultNumbersBits[0] })), 0u);
	EXPECT_EQ(DecodeMessage(decoder, std::vector<uint32_t>({ c_defaultNumbersBits[3] })), 3u);
	EXPECT_EQ(DecodeMessage(decoder, std::vector<uint32_t>({ c_defaultNumbersBits[9] })), 9u);
}

TEST(Day8, DecodeLongMessage)
{
	std::array<uint32_t, 10> decoder = CreateDecoderFromTestSignal(std::vector<uint32_t>(std::begin(c_defaultNumbersBits), std::end(c_defaultNumbersBits)));

	EXPECT_EQ(DecodeMessage(decoder, std::vector<uint32_t>({ c_defaultNumbersBits[9], c_defaultNumbersBits[1], c_defaultNumbersBits[2] })), 912u);
}

TEST(Day8, DecodeExampleLine)
{
	std::istringstream input{ c_exampleLine };
	std::vector<uint32_t> code;
	std::vector<uint32_t> message;
	GetBitsCodeAndMessage(input, code, message);
	EXPECT_EQ(DecodeMessage(CreateDecoderFromTestSignal(code), message), 5353u);
}

TEST(Day8, DecodeExampleInput)
{
	std::istringstream input(c_exampleInput);
	uint32_t output = 0u;
	std::vector<uint32_t> code;
	std::vector<uint32_t> message;
	while (GetBitsCodeAndMessage(input, code, message))
	{
		output += DecodeMessage(CreateDecoderFromTestSignal(code), message);
	}
	EXPECT_EQ(output, 61229u);
}
