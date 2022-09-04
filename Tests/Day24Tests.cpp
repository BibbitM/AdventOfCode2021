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

TEST(Day24, IntVector4GetCoordinateByIndex)
{
	IntVector4 vec{ 1, -2, 30, 400 };
	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], -2);
	EXPECT_EQ(vec[2], 30);
	EXPECT_EQ(vec[3], 400);
}

TEST(Day24, IntVector4SetCoordinateByIndex)
{
	IntVector4 vec{};
	vec[0] = 1;
	vec[1] = -2;
	vec[2] = 30;
	vec[3] = 400;
	EXPECT_EQ(vec, IntVector4(1, -2, 30, 400));
}

TEST(Day24, DefaultAluState)
{
	Monad::Alu alu;
	EXPECT_EQ(alu.GetRegisters(), IntVector4());
}

TEST(Day24, AluReadsInput)
{
	Monad::Alu alu;

	alu.Inp(0, 3);
	EXPECT_EQ(alu.GetRegisters().x, 3);
	alu.Inp(1, 123);
	EXPECT_EQ(alu.GetRegisters().y, 123);
	alu.Inp(2, -1);
	EXPECT_EQ(alu.GetRegisters().z, -1);
	alu.Inp(3, -100);
	EXPECT_EQ(alu.GetRegisters().w, -100);

	EXPECT_EQ(alu.GetRegisters(), IntVector4(3, 123, -1, -100));
}
