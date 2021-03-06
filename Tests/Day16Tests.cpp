#include "pch.h"

#include "../Code/Transmission.h"

#include <sstream>

TEST(Day16, EmptyTransmission)
{
	Transmission transmission;

	EXPECT_EQ(transmission.GetLength(), 0);
}

TEST(Day16, LoadSingleChar)
{
	Transmission transmission;
	std::istringstream input("0");

	input >> transmission;

	EXPECT_EQ(transmission.GetLength(), 4);
	EXPECT_EQ(transmission.ReadBits(4), 0u);
}

TEST(Day16, LoadMulitpleChars)
{
	Transmission transmission;
	std::istringstream input("AF09C5");

	input >> transmission;

	EXPECT_EQ(transmission.GetLength(), 4 * 6);
	EXPECT_EQ(transmission.ReadBits(4), 0b1010u);
	EXPECT_EQ(transmission.ReadBits(4), 0b1111u);
	EXPECT_EQ(transmission.ReadBits(4), 0b0000u);
	EXPECT_EQ(transmission.ReadBits(4), 0b1001u);
	EXPECT_EQ(transmission.ReadBits(4), 0b1100u);
	EXPECT_EQ(transmission.ReadBits(4), 0b0101u);
}

TEST(Day16, LoadExamleSimpleMessage)
{
	Transmission transmission;
	std::istringstream input("D2FE28");

	input >> transmission;

	EXPECT_EQ(transmission.ReadBits(3), 0b110u);
	EXPECT_EQ(transmission.ReadBits(3), 0b100u);
	EXPECT_EQ(transmission.ReadBits(5), 0b10111u);
	EXPECT_EQ(transmission.ReadBits(5), 0b11110u);
	EXPECT_EQ(transmission.ReadBits(5), 0b00101u);
	EXPECT_EQ(transmission.ReadBits(3), 0b000u);
}

TEST(Day16, ReadPacket4Version)
{
	Transmission transmission;
	std::istringstream input("D2FE28");

	input >> transmission;

	EXPECT_EQ(ReadPacketVersion(transmission), 6u);
	EXPECT_EQ(transmission.GetPosition(), 21); //< Make sure we read packed to the end.
}

TEST(Day16, ReadMultiPacketVersion)
{
	{
		Transmission transmission;
		std::istringstream input("8A004A801A8002F478");

		input >> transmission;

		EXPECT_EQ(ReadPacketVersion(transmission), 16u);
	}

	{
		Transmission transmission;
		std::istringstream input("C0015000016115A2E0802F182340");

		input >> transmission;

		EXPECT_EQ(ReadPacketVersion(transmission), 23u);
	}

	{
		Transmission transmission;
		std::istringstream input("A0016C880162017C3686B18A3D4780");

		input >> transmission;

		EXPECT_EQ(ReadPacketVersion(transmission), 31u);
	}
}

TEST(Day16, ReadValueSimple)
{
	Transmission transmission;
	std::istringstream input("D2FE28");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 2021u);
}

TEST(Day16, ReadValueSum)
{
	Transmission transmission;
	std::istringstream input("C200B40A82");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 3u);
}

TEST(Day16, ReadValueProduct)
{
	Transmission transmission;
	std::istringstream input("04005AC33890");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 54u);
}

TEST(Day16, ReadValueMinimum)
{
	Transmission transmission;
	std::istringstream input("880086C3E88112");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 7u);
}

TEST(Day16, ReadValueMaximum)
{
	Transmission transmission;
	std::istringstream input("CE00C43D881120");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 9u);
}

TEST(Day16, ReadValueLess)
{
	Transmission transmission;
	std::istringstream input("D8005AC2A8F0");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 1u);
}

TEST(Day16, ReadValueGreater)
{
	Transmission transmission;
	std::istringstream input("F600BC2D8F");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 0u);
}

TEST(Day16, ReadValueNotEqual)
{
	Transmission transmission;
	std::istringstream input("9C005AC2F8F0");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 0u);
}

TEST(Day16, ReadValueEqual)
{
	Transmission transmission;
	std::istringstream input("9C0141080250320F1802104A08");

	input >> transmission;

	EXPECT_EQ(ReadPacketValue(transmission), 1u);
}

TEST(Day16, ResetTransmission)
{
	Transmission tranmission;
	std::istringstream input("04005AC33890");

	input >> tranmission;

	EXPECT_EQ(tranmission.GetPosition(), 0u);
	ReadPacketValue(tranmission);
	EXPECT_NE(tranmission.GetPosition(), 0u);
	tranmission.Reset();
	EXPECT_EQ(tranmission.GetPosition(), 0u);
}
