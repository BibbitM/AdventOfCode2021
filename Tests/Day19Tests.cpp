#include "pch.h"

#include "../Code/IntVector3.h"
#include "../Code/Scanner.h"

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

TEST(Day19, ScannerEmpty)
{
	Scanner scanner{};

	EXPECT_EQ(scanner.BeaconsCount(), 0);
}

TEST(Day19, ScannerCreateFromVector)
{
	Scanner scanner({ { 1, 2, 3 }, { 4, 5, 6 } });
	EXPECT_EQ(scanner.BeaconsCount(), 2);
	EXPECT_EQ(Scanner({ { 0, 0, 1 }, { 1, 0, 0 }, { 1, 0, 0 } }).BeaconsCount(), 3);
}

TEST(Day19, ScannerLoadFromInput)
{
	{
		Scanner scanner;
		std::istringstream input{ R"--(--- scanner 0 ---
1,1,1
)--"
		};
		input >> scanner;
		EXPECT_EQ(scanner.BeaconsCount(), 1);
	}

	{
		Scanner scanner;
		std::istringstream input{ R"--(--- scanner 0 ---
-1,-1,1
-2,-2,2
-3,-3,3
-2,-3,1
5,6,-4
8,0,7
)--"
		};
		input >> scanner;
		EXPECT_EQ(scanner.BeaconsCount(), 6);
	}
}

TEST(Day19, ScannerLoadFromInputOnlyOne)
{
	Scanner scanner;
	std::istringstream input{ R"--(--- scanner 1 ---
686,422,578
605,423,415
515,917,-361

--- scanner 0 ---
-1,-1,1
-2,-2,2
-3,-3,3
-2,-3,1
5,6,-4
8,0,7
)--"
	};
	input >> scanner;
	EXPECT_EQ(scanner.BeaconsCount(), 3);
}

TEST(Day19, MergeNotOverlappingReturnsFalse)
{
	Scanner scanner0({ { 1, 1, 1 }, { 100, 100, 100 } });
	Scanner scanner1({ { 2, 2, 2 }, { 200, 200, 200 } });

	EXPECT_FALSE(scanner0.Merge(scanner1, 2));
}

TEST(Day19, MergeTwoScannersTheSameOrigin)
{
	Scanner scanner0({ { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 } });
	Scanner scanner1({ { 1, 1, 1 }, { 1, 0, 0 }, { 0, 0, 1 } });

	EXPECT_TRUE(scanner0.Merge(scanner1, 3));
}

TEST(Day19, MergeTwoScannersTheDifferentOrigin)
{
	Scanner scanner0({ { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 } });
	Scanner scanner1({ { 101, 101, 101 }, { 101, 100, 100 }, { 100, 100, 101 } });

	EXPECT_TRUE(scanner0.Merge(scanner1, 3));
}
