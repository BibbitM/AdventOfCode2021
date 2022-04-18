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

TEST(Day19, IntVector3Add)
{
	EXPECT_EQ(IntVector3(0, 1, 2) + IntVector3(10, 20, 30), IntVector3(10, 21, 32));
}

TEST(Day19, IntVector3Sub)
{
	EXPECT_EQ(IntVector3(0, 1, 2) - IntVector3(10, -20, 30), IntVector3(-10, 21, -28));
}

TEST(Day19, IntVector3GetCoordinateByIndex)
{
	IntVector3 vec{ 1, -2, 30 };
	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], -2);
	EXPECT_EQ(vec[2], 30);
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

TEST(Day19, MergeOldNotOverlappingReturnsFalse)
{
	Scanner scanner0({ { 1, 1, 1 }, { 100, 100, 100 } });
	Scanner scanner1({ { 2, 2, 2 }, { 200, 200, 200 } });

	EXPECT_FALSE(scanner0.MergeOld(scanner1, 2));
}

TEST(Day19, MergeOldTwoScannersTheSameOrigin)
{
	Scanner scanner0({ { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 } });
	Scanner scanner1({ { 1, 1, 1 }, { 1, 0, 0 }, { 0, 0, 1 } });

	EXPECT_TRUE(scanner0.MergeOld(scanner1, 3));
	EXPECT_EQ(scanner0.BeaconsCount(), 3);
}

TEST(Day19, MergeOldTwoScannersTheDifferentOrigin)
{
	Scanner scanner0({ { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 } });
	Scanner scanner1({ { 101, 101, 101 }, { 101, 100, 100 }, { 100, 100, 101 } });

	EXPECT_TRUE(scanner0.MergeOld(scanner1, 3));
	EXPECT_EQ(scanner0.BeaconsCount(), 3);
}

TEST(Day19, MergeOldTwoScannersAddsExtraBeacon)
{
	Scanner scanner0({ { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 }, { 20, 30, 20 } });
	Scanner scanner1({ { 101, 101, 101 }, { 104, 104, 104 }, { 101, 100, 100 }, { 120, 130, 120 }, { 100, 100, 101 } });

	EXPECT_EQ(scanner0.BeaconsCount(), 4);
	EXPECT_FALSE(scanner0.ContainsBeacon({ 4, 4, 4 }));

	EXPECT_TRUE(scanner0.MergeOld(scanner1, 3));

	EXPECT_EQ(scanner0.BeaconsCount(), 5);
	EXPECT_TRUE(scanner0.ContainsBeacon({ 4, 4, 4 }));
}

TEST(Day19, MergeOldTwoScannersAddsExtraBeaconDifferentOrientationAndSign)
{
	Scanner scanner0({
			{ 1,1,-1 },
			{ 2,2,-2 },
			{ 3,3,-3 },
			{ 1,3,-2 },
			{ -4,-6,5 },
			{ 7, 0, 8 }
		});
	Scanner scanner1({
			{ 1,1,1 },
			{ 2,2,2 },
			{ 3,3,3 },
			{ 3,1,2 },
			{ -6,-4,-5 },
			{ 0,7,-8 },
			{ 20, 10, -30 }
		});


	EXPECT_EQ(scanner0.BeaconsCount(), 6);
	EXPECT_FALSE(scanner0.ContainsBeacon({ 10, 20, 30 }));

	EXPECT_TRUE(scanner0.MergeOld(scanner1, 6));

	EXPECT_EQ(scanner0.BeaconsCount(), 7);
	EXPECT_TRUE(scanner0.ContainsBeacon({ 10, 20, 30 }));
}

TEST(Day19, OverlapNotOverlappingReturnsFalse)
{
	const Scanner scanner0({ { 1, 1, 1 }, { 100, 100, 100 } });
	Scanner scanner1({ { 2, 2, 2 }, { 200, 200, 200 } });

	EXPECT_FALSE(scanner1.OverlapWith(scanner0, 2));
}

TEST(Day19, OverlapTwoScannersTheSameOrigin)
{
	const Scanner scanner0({ { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 } });
	Scanner scanner1({ { 1, 1, 1 }, { 1, 0, 0 }, { 0, 0, 1 } });

	EXPECT_TRUE(scanner1.OverlapWith(scanner0, 3));
	EXPECT_EQ(scanner1.GetOffset(), IntVector3(0, 0, 0));
}

TEST(Day19, OverlapTwoScannersTheDifferentOrigin)
{
	const Scanner scanner0({ { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 } });
	Scanner scanner1({ { 101, 101, 101 }, { 101, 100, 100 }, { 100, 100, 101 } });

	EXPECT_TRUE(scanner1.OverlapWith(scanner0, 3));
	EXPECT_EQ(scanner1.GetOffset(), IntVector3(-100, -100, -100));
}

TEST(Day19, OverlapThreeScannersAddsOffset)
{
	const Scanner scanner0({ { 1, 1, 1 } });
	Scanner scanner1({ { 101, 101, 101 } });
	Scanner scanner2({ { 51, 51, 51 } });

	EXPECT_TRUE(scanner1.OverlapWith(scanner0, 1));
	EXPECT_TRUE(scanner2.OverlapWith(scanner1, 1));
	EXPECT_EQ(scanner2.GetOffset(), IntVector3(-50, -50, -50));
}

TEST(Day19, OverlapMergeTwoScannersAddsExtraBeacon)
{
	Scanner scanner0({ { 1, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 }, { 20, 30, 20 } });
	Scanner scanner1({ { 101, 101, 101 }, { 104, 104, 104 }, { 101, 100, 100 }, { 120, 130, 120 }, { 100, 100, 101 } });

	EXPECT_EQ(scanner0.BeaconsCount(), 4);
	EXPECT_FALSE(scanner0.ContainsBeacon({ 4, 4, 4 }));

	EXPECT_TRUE(scanner1.OverlapWith(scanner0, 3));
	scanner0.Merge(scanner1);

	EXPECT_EQ(scanner0.BeaconsCount(), 5);
	EXPECT_TRUE(scanner0.ContainsBeacon({ 4, 4, 4 }));
}

TEST(Day19, OverlapMergeTheeScannersAddsExtraBeacon)
{
	Scanner scanner0({ { 1, 1, 1 } });
	Scanner scanner1({ { 101, 101, 101 } });
	Scanner scanner2({ { 51, 51, 51 }, { 52, 52, 52 } });

	EXPECT_TRUE(scanner1.OverlapWith(scanner0, 1));
	EXPECT_TRUE(scanner2.OverlapWith(scanner1, 1));

	scanner1.Merge(scanner2);
	EXPECT_EQ(scanner1.BeaconsCount(), 2);
	EXPECT_TRUE(scanner1.ContainsBeacon({ 102, 102, 102 }));

	scanner0.Merge(scanner1);
	EXPECT_EQ(scanner0.BeaconsCount(), 2);
	EXPECT_TRUE(scanner0.ContainsBeacon({ 2, 2, 2 }));

	scanner0.Merge(scanner2);
	EXPECT_EQ(scanner0.BeaconsCount(), 2);
}

TEST(Day19, OverlapMergeTwoScannersAddsExtraBeaconDifferentOrientationAndSign)
{
	Scanner scanner0({
			{ 1,1,-1 },
			{ 2,2,-2 },
			{ 3,3,-3 },
			{ 1,3,-2 },
			{ -4,-6,5 },
			{ 7, 0, 8 }
		});
	Scanner scanner1({
			{ 1,1,1 },
			{ 2,2,2 },
			{ 3,3,3 },
			{ 3,1,2 },
			{ -6,-4,-5 },
			{ 0,7,-8 },
			{ 20, 10, -30 }
		});


	EXPECT_EQ(scanner0.BeaconsCount(), 6);
	EXPECT_FALSE(scanner0.ContainsBeacon({ 10, 20, 30 }));

	EXPECT_TRUE(scanner1.OverlapWith(scanner0, 6));
	scanner0.Merge(scanner1);

	EXPECT_EQ(scanner0.BeaconsCount(), 7);
	EXPECT_TRUE(scanner0.ContainsBeacon({ 10, 20, 30 }));
}
