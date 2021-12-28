#include "pch.h"

extern void fnCode();

TEST(TestCaseName, TestName)
{
	fnCode();
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}
