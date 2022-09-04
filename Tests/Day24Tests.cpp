#include "pch.h"

#include "../Code/IntVector4.h"
#include "../Code/Monad.h"

TEST(Day24, IntVector4CreateEmpty)
{
	IntVector4 vec{};

	EXPECT_EQ(vec.x, 0);
	EXPECT_EQ(vec.y, 0);
	EXPECT_EQ(vec.z, 0);
	EXPECT_EQ(vec.w, 0);
}

TEST(Day24, IntVector4CreateXYZW)
{
	IntVector4 vec{ 10, 20, 30, 40 };

	EXPECT_EQ(vec.x, 10);
	EXPECT_EQ(vec.y, 20);
	EXPECT_EQ(vec.z, 30);
	EXPECT_EQ(vec.w, 40);
}

TEST(Day24, IntVector4Equals)
{
	IntVector4 vec{ 1, 2, 3, 4 };
	IntVector4 vecEq = vec;
	IntVector4 vecNe{ 4, 3, 2, 1 };

	EXPECT_EQ(vec, vecEq);
	EXPECT_NE(vec, vecNe);
}
TEST(Day24, DefaultAluState)
{
	Monad::Alu alu;
	EXPECT_EQ(alu.GetRegisters(), IntVector4());
}
