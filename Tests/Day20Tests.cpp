#include "pch.h"

#include "../Code/ScannerImage.h"

TEST(Day20, ScannerImageEmpty)
{
	ScannerImage image;

	EXPECT_EQ(image.GetWidth(), 0);
	EXPECT_EQ(image.GetHeight(), 0);
}
