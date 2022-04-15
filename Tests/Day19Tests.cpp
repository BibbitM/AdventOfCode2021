#include "pch.h"

#include "../Code/IntVector3.h"

#include <sstream>

TEST(Day19, IntVector3CreateEmpty)
{
	IntVector3 vec{};

	EXPECT_EQ(vec.x, 0);
	EXPECT_EQ(vec.y, 0);
	EXPECT_EQ(vec.z, 0);
}

TEST(Day19, IntVector3CreateXYZ)
{
	IntVector3 vec{ 10, 20, 30 };

	EXPECT_EQ(vec.x, 10);
	EXPECT_EQ(vec.y, 20);
	EXPECT_EQ(vec.z, 30);
}

TEST(Day19, IntVector3Equals)
{
	IntVector3 vec{ 1, 2, 3 };
	IntVector3 vecEq = vec;
	IntVector3 vecNe{ 3, 2, 1 };

	EXPECT_EQ(vec, vecEq);
	EXPECT_NE(vec, vecNe);
}

TEST(Day19, IntVector3Distance)
{
	EXPECT_EQ(Distance2(IntVector3{}, IntVector3{}), 0);
	EXPECT_EQ(Distance2(IntVector3{}, IntVector3{ 1, 1, 1 }), 3);
	EXPECT_EQ(Distance2(IntVector3{}, IntVector3{ 1, 2, 3 }), 14);
	EXPECT_EQ(Distance2(IntVector3{ 1, 2, 3 }, IntVector3{}), 14);
	EXPECT_EQ(Distance2(IntVector3{ -10, 100, 0 }, IntVector3{ 0, 0, -1000 }), 1010100);
}

TEST(Day19, IntVector3LoadFromInput)
{
	{
		std::istringstream input{ "1,2,3" };
		IntVector3 vec{};
		input >> vec;
		EXPECT_EQ(vec, IntVector3(1, 2, 3));
	}

	{
		std::istringstream input{ "459,-707,401" };
		IntVector3 vec{};
		input >> vec;
		EXPECT_EQ(vec, IntVector3(459, -707, 401));
	}
}
