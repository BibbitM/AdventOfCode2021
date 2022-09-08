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

	alu.Inp(Monad::X, 3);
	EXPECT_EQ(alu.GetRegisters().x, 3);
	alu.Inp(Monad::Y, 123);
	EXPECT_EQ(alu.GetRegisters().y, 123);
	alu.Inp(Monad::Z, -1);
	EXPECT_EQ(alu.GetRegisters().z, -1);
	alu.Inp(Monad::W, -100);
	EXPECT_EQ(alu.GetRegisters().w, -100);

	EXPECT_EQ(alu.GetRegisters(), IntVector4(3, 123, -1, -100));
}

TEST(Day24, AluAddsValue)
{
	Monad::Alu alu;

	alu.AddV(Monad::X, 10);
	EXPECT_EQ(alu.GetRegisters().x, 10);
	alu.AddV(Monad::X, -20);
	EXPECT_EQ(alu.GetRegisters().x, -10);

	alu.AddV(Monad::Y, 2);
	EXPECT_EQ(alu.GetRegisters().y, 2);

	alu.AddV(Monad::Z, -333);
	EXPECT_EQ(alu.GetRegisters().z, -333);

	alu.AddV(Monad::W, 4);
	EXPECT_EQ(alu.GetRegisters().w, 4);

	EXPECT_EQ(alu.GetRegisters(), IntVector4(-10, 2, -333, 4));
}

TEST(Day24, AluAddsRegister)
{
	Monad::Alu alu;

	alu.Inp(Monad::X, 1);
	alu.Inp(Monad::Y, 20);
	alu.Inp(Monad::Z, -30);
	alu.Inp(Monad::W, -400);

	alu.AddR(Monad::X, Monad::X);
	EXPECT_EQ(alu.GetRegisters().x, 2);
	alu.AddR(Monad::Y, Monad::X);
	EXPECT_EQ(alu.GetRegisters().x, 2);
	EXPECT_EQ(alu.GetRegisters().y, 22);
	alu.AddR(Monad::Z, Monad::Y);
	EXPECT_EQ(alu.GetRegisters().z, -8);
	alu.AddR(Monad::Z, Monad::W);
	EXPECT_EQ(alu.GetRegisters().z, -408);
	alu.AddR(Monad::W, Monad::Z);
	EXPECT_EQ(alu.GetRegisters().w, -808);

	EXPECT_EQ(alu.GetRegisters(), IntVector4(2, 22, -408, -808));
}

TEST(Day24, AluMultipliesByValue)
{
	Monad::Alu alu;

	alu.Inp(Monad::X, 1);
	alu.Inp(Monad::Y, -2);
	alu.Inp(Monad::Z, 3);
	alu.Inp(Monad::W, -5);

	alu.MulV(Monad::X, 7);
	EXPECT_EQ(alu.GetRegisters().x, 7);
	alu.MulV(Monad::Y, 11);
	EXPECT_EQ(alu.GetRegisters().y, -22);
	alu.MulV(Monad::Z, -13);
	EXPECT_EQ(alu.GetRegisters().z, -39);
	alu.MulV(Monad::W, -17);
	EXPECT_EQ(alu.GetRegisters().w, 85);
	alu.MulV(Monad::W, 0);
	EXPECT_EQ(alu.GetRegisters().w, 0);

	EXPECT_EQ(alu.GetRegisters(), IntVector4(7, -22, -39, 0));
}

TEST(Day24, AluMultipliesByRegister)
{
	Monad::Alu alu;

	alu.Inp(Monad::X, 1);
	alu.Inp(Monad::Y, -2);
	alu.Inp(Monad::Z, 3);
	alu.Inp(Monad::W, -5);

	alu.MulR(Monad::X, Monad::X);
	EXPECT_EQ(alu.GetRegisters().x, 1);
	alu.MulR(Monad::X, Monad::Y);
	EXPECT_EQ(alu.GetRegisters().x, -2);
	alu.MulR(Monad::Y, Monad::X);
	EXPECT_EQ(alu.GetRegisters().y, 4);
	alu.MulR(Monad::Z, Monad::Y);
	EXPECT_EQ(alu.GetRegisters().z, 12);
	alu.MulR(Monad::W, Monad::Z);
	EXPECT_EQ(alu.GetRegisters().w, -60);

	EXPECT_EQ(alu.GetRegisters(), IntVector4(-2, 4, 12, -60));
}

TEST(Day24, AluDividesByValue)
{
	Monad::Alu alu;

	alu.Inp(Monad::X, 1);
	alu.DivV(Monad::X, 1);
	EXPECT_EQ(alu.GetRegisters().x, 1);
	alu.DivV(Monad::X, 2);
	EXPECT_EQ(alu.GetRegisters().x, 0);

	alu.Inp(Monad::Y, 5);
	alu.DivV(Monad::Y, -3);
	EXPECT_EQ(alu.GetRegisters().y, -1);

	alu.Inp(Monad::Z, -11);
	alu.DivV(Monad::Z, 5);
	EXPECT_EQ(alu.GetRegisters().z, -2);

	alu.Inp(Monad::W, -17);
	alu.DivV(Monad::W, -3);
	EXPECT_EQ(alu.GetRegisters().w, 5);
}
