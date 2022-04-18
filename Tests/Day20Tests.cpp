#include "pch.h"

#include "../Code/ScannerImage.h"

#include <sstream>
#include <string_view>
#include <vector>

namespace
{
	constexpr char c_exampleEnhancement[] =
		"..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..##"
		"#..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###"
		".######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#."
		".#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#....."
		".#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.."
		"...####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#....."
		"..##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#";
	constexpr char c_exampleImage[] =
		"#..#.\n"
		"#....\n"
		"##..#\n"
		"..#..\n"
		"..###\n";
	constexpr char c_exampleImageEnhanced[] =
		".........\n"
		"..##.##..\n"
		".#..#.#..\n"
		".##.#..#.\n"
		".####..#.\n"
		"..#..##..\n"
		"...##..#.\n"
		"....#.#..\n"
		".........\n";
	constexpr char c_exampleImageEnhancedTwice[] =
		".............\n"
		".............\n"
		".........#...\n"
		"...#..#.#....\n"
		"..#.#...###..\n"
		"..#...##.#...\n"
		"..#.....#.#..\n"
		"...#.#####...\n"
		"....#.#####..\n"
		".....##.##...\n"
		"......###....\n"
		".............\n"
		".............\n";
}

TEST(Day20, VectorBoolAppendByEmptyString)
{
	std::vector<bool> vec;

	AppendBoolVectorByString(vec, "");

	EXPECT_TRUE(vec.empty());
}

TEST(Day20, VectorBoolAppendByExampleString)
{
	std::vector<bool> vec;

	AppendBoolVectorByString(vec, "#..#");

	EXPECT_EQ(vec.size(), 4);
	EXPECT_EQ(vec[0], true);
	EXPECT_EQ(vec[1], false);
	EXPECT_EQ(vec[2], false);
	EXPECT_EQ(vec[3], true);

	AppendBoolVectorByString(vec, ".#");

	EXPECT_EQ(vec.size(), 6);
	EXPECT_EQ(vec[4], false);
	EXPECT_EQ(vec[5], true);
}

TEST(Day20, ScannerImageEmpty)
{
	ScannerImage image;

	EXPECT_EQ(image.GetWidth(), 0);
	EXPECT_EQ(image.GetHeight(), 0);
	EXPECT_EQ(image.CountLitPixels(), 0);
}

TEST(Day20, ScannerImageCreateGivenSize)
{
	ScannerImage image(10, 4);

	EXPECT_EQ(image.GetWidth(), 10);
	EXPECT_EQ(image.GetHeight(), 4);
	EXPECT_EQ(image.CountLitPixels(), 0);
}

TEST(Day20, ScannerImageLoadEmptyFromInput)
{
	ScannerImage image;
	std::istringstream input("....\n....\n....");

	input >> image;

	EXPECT_EQ(image.GetWidth(), 4);
	EXPECT_EQ(image.GetHeight(), 3);
	EXPECT_EQ(image.CountLitPixels(), 0);
	EXPECT_EQ(image.Get(0, 0), false);
}

TEST(Day20, ScannerImageLoadExampleFromInput)
{
	ScannerImage image;
	std::istringstream input{ c_exampleImage };

	input >> image;

	EXPECT_EQ(image.GetWidth(), 5);
	EXPECT_EQ(image.GetHeight(), 5);
	EXPECT_EQ(image.CountLitPixels(), 10);
	EXPECT_EQ(image.Get(0, 0), true);
	EXPECT_EQ(image.Get(1, 0), false);
	EXPECT_EQ(image.Get(0, 1), true);
	EXPECT_EQ(image.Get(1, 1), false);
	EXPECT_EQ(image.Get(0, 2), true);
	EXPECT_EQ(image.Get(1, 2), true);
	EXPECT_EQ(image.Get(4, 4), true);
}

TEST(Day20, ScannerImageGetOutsideRangeReturnsFalse)
{
	ScannerImage image;
	std::istringstream input("#");

	input >> image;

	EXPECT_EQ(image.GetWidth(), 1);
	EXPECT_EQ(image.GetHeight(), 1);
	EXPECT_EQ(image.CountLitPixels(), 1);
	EXPECT_EQ(image.Get(0, 0), true);

	EXPECT_EQ(image.Get(-1, -1), false);
	EXPECT_EQ(image.Get(1, 1), false);
	EXPECT_EQ(image.Get(-100, 0), false);
	EXPECT_EQ(image.Get(4, 0), false);
	EXPECT_EQ(image.Get(0, -3), false);
	EXPECT_EQ(image.Get(0, 5), false);
}

TEST(Day20, ScannerImageSetPixelValue)
{
	ScannerImage image(2, 2);

	image.Set(0, 0, true);
	EXPECT_EQ(image.Get(0, 0), true);
	image.Set(1, 1, false);
	EXPECT_EQ(image.Get(1, 1), false);
}

TEST(Day20, ScannerImageGetEnhancedPixel)
{
	{
		ScannerImage image;
		EXPECT_EQ(image.GetEnhanced(0, 0), 0b0);
	}

	{
		ScannerImage image;
		std::istringstream input{ c_exampleImage };

		input >> image;

		EXPECT_EQ(image.GetEnhanced(2, 2), 0b000100010);
	}
}

TEST(Day20, ScannerImageExtendEmptyImage)
{
	ScannerImage image;
	ScannerImage loadedEnhancedImage;
	ScannerImage loadedEnhancedImageTwice;

	{
		std::istringstream input{ c_exampleImage };
		input >> image;
	}
	{
		std::istringstream input{ c_exampleImageEnhanced };
		input >> loadedEnhancedImage;
	}
	{
		std::istringstream input{ c_exampleImageEnhancedTwice };
		input >> loadedEnhancedImageTwice;
	}

	std::vector<bool> enhacementAlgorithm;
	AppendBoolVectorByString(enhacementAlgorithm, c_exampleEnhancement);
	EXPECT_EQ(enhacementAlgorithm.size(), 512);

	ScannerImage enhancedImage = image.Enhance(enhacementAlgorithm);
	EXPECT_EQ(enhancedImage.GetWidth(), image.GetWidth() + 4);
	EXPECT_EQ(enhancedImage.GetHeight(), image.GetHeight() + 4);
	EXPECT_EQ(enhancedImage, loadedEnhancedImage);

	ScannerImage enhancedImageTwice = enhancedImage.Enhance(enhacementAlgorithm);
	EXPECT_EQ(enhancedImageTwice, loadedEnhancedImageTwice);
	EXPECT_EQ(enhancedImageTwice.CountLitPixels(), 35);
}
