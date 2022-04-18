#include "pch.h"

#include "../Code/ScannerImage.h"

TEST(Day20, ScannerImageEmpty)
{
	ScannerImage image;

	EXPECT_EQ(image.GetWidth(), 0);
	EXPECT_EQ(image.GetHeight(), 0);
}

TEST(Day20, ScannerImageCreateGivenSize)
{
	ScannerImage image(10, 4);

	EXPECT_EQ(image.GetWidth(), 10);
	EXPECT_EQ(image.GetHeight(), 4);
}
