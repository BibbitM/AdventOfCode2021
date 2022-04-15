#include "pch.h"

#include "../Code/SnailfishNumber.h"

TEST(Day18, EmptyNumberHasZeroMagnitude)
{
	Snailfish::Number empty;
	EXPECT_EQ(empty.Magnitude(), 0);
}

TEST(Day18, SimpleNumberMagnitude)
{
	EXPECT_EQ(Snailfish::Number(0, 0).Magnitude(), 0);
	EXPECT_EQ(Snailfish::Number(5, 0).Magnitude(), 5 * 3);
	EXPECT_EQ(Snailfish::Number(0, 4).Magnitude(), 4 * 2);
	EXPECT_EQ(Snailfish::Number(9, 1).Magnitude(), 29);
	EXPECT_EQ(Snailfish::Number(1, 9).Magnitude(), 21);
}

TEST(Day18, CompareNumbers)
{
	EXPECT_EQ(Snailfish::Number(0, 0), Snailfish::Number());
	EXPECT_EQ(Snailfish::Number(1, 2), Snailfish::Number(1, 2));

	EXPECT_NE(Snailfish::Number(9, 9), Snailfish::Number());
	EXPECT_NE(Snailfish::Number(5, 3), Snailfish::Number(2, 1));
}

TEST(Day18, CreateSimpleNumberFromString)
{
	EXPECT_EQ(Snailfish::Number("[0,0]"), Snailfish::Number(0, 0));
	EXPECT_EQ(Snailfish::Number("[4,2]"), Snailfish::Number(4, 2));
}

TEST(Day18, ConvertNumberToString)
{
	EXPECT_EQ(Snailfish::Number("[0,0]").ToString(), "[0,0]");
	EXPECT_EQ(Snailfish::Number("[1,2]").ToString(), "[1,2]");
	EXPECT_EQ(Snailfish::Number("[[[[0,9],2],3],4]").ToString(), "[[[[0,9],2],3],4]");
	EXPECT_EQ(Snailfish::Number("[[1,2],[3,4]]").ToString(), "[[1,2],[3,4]]");
}

TEST(Day18, CreateNumberFromStringLiteral)
{
	EXPECT_EQ("[1,2]"_SN, Snailfish::Number(1, 2));
	EXPECT_EQ("[[1,2],[3,[[4,5],6]]]"_SN, Snailfish::Number("[[1,2],[3,[[4,5],6]]]"));
}

TEST(Day18, AddSimpleNumbersMagnitude)
{
	EXPECT_EQ((Snailfish::Number("[0,0]") + Snailfish::Number("[0,0]")).Magnitude(), 0);
	EXPECT_EQ((Snailfish::Number("[1,0]") + Snailfish::Number("[0,2]")).Magnitude(), 17);
}

TEST(Day18, SimpleSumCreatesComplexNumber)
{
	EXPECT_EQ(Snailfish::Number("[0,0]") + Snailfish::Number("[0,0]"), Snailfish::Number("[[0,0],[0,0]]"));
	EXPECT_EQ(Snailfish::Number("[1,2]") + Snailfish::Number("[3,4]"), Snailfish::Number("[[1,2],[3,4]]"));
}

TEST(Day18, ExplodeComplexNumberToString)
{
	EXPECT_EQ(Snailfish::Number("[[[[[9,8],1],2],3],4]").ToString(), "[[[[0,9],2],3],4]");
	EXPECT_EQ(Snailfish::Number("[7,[6,[5,[4,[3,2]]]]]").ToString(), "[7,[6,[5,[7,0]]]]");
	EXPECT_EQ(Snailfish::Number("[[6,[5,[4,[3,2]]]],1]").ToString(), "[[6,[5,[7,0]]],3]");
	// Partial reductions steps.
	//EXPECT_EQ(Snailfish::Number("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]").ToString(), "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]");
	//EXPECT_EQ(Snailfish::Number("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]").ToString(), "[[3,[2,[8,0]]],[9,[5,[7,0]]]]");
	EXPECT_EQ(Snailfish::Number("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]").ToString(), "[[3,[2,[8,0]]],[9,[5,[7,0]]]]");
	EXPECT_EQ(Snailfish::Number("[[[[[2,3],4],5],6],[[[[3,7],1],2],3]]").ToString(), "[[[[0,7],5],9],[[[0,8],2],3]]");
}

TEST(Day18, ExplodeComplexNumber)
{
	EXPECT_EQ(Snailfish::Number("[[[[[9,8],1],2],3],4]"), Snailfish::Number("[[[[0,9],2],3],4]"));
	EXPECT_EQ(Snailfish::Number("[7,[6,[5,[4,[3,2]]]]]"), Snailfish::Number("[7,[6,[5,[7,0]]]]"));
	EXPECT_EQ(Snailfish::Number("[[6,[5,[4,[3,2]]]],1]"), Snailfish::Number("[[6,[5,[7,0]]],3]"));
	EXPECT_EQ(Snailfish::Number("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]"), Snailfish::Number("[[3,[2,[8,0]]],[9,[5,[7,0]]]]"));
}

TEST(Day18, SplitSimpleNumber)
{
	EXPECT_EQ(Snailfish::Number("[10,1]").ToString(), "[[5,5],1]");
	EXPECT_EQ(Snailfish::Number("[2,11]").ToString(), "[2,[5,6]]");
}

TEST(Day18, SplitAndReduceExampleNumberToString)
{
	EXPECT_EQ(Snailfish::Number("[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]").ToString(), "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
}

TEST(Day18, AddSplitAndReduceExampleNubers)
{
	EXPECT_EQ(Snailfish::Number("[[[[4,3],4],4],[7,[[8,4],9]]]") + Snailfish::Number("[1,1]"), Snailfish::Number("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]"));
}

TEST(Day18, SimpleExamplesAdd)
{
	EXPECT_EQ(
		"[1,1]"_SN + "[2,2]"_SN + "[3,3]"_SN + "[4,4]"_SN,
		"[[[[1,1],[2,2]],[3,3]],[4,4]]"_SN
		);
	EXPECT_EQ(
		"[1,1]"_SN + "[2,2]"_SN + "[3,3]"_SN + "[4,4]"_SN + "[5,5]"_SN,
		"[[[[3,0],[5,3]],[4,4]],[5,5]]"_SN
		);
	EXPECT_EQ(
		"[1,1]"_SN + "[2,2]"_SN + "[3,3]"_SN + "[4,4]"_SN + "[5,5]"_SN + "[6,6]"_SN,
		"[[[[5,0],[7,4]],[5,5]],[6,6]]"_SN
		);
}

TEST(Day18, LargerExamplesAdd)
{
	EXPECT_EQ(
		  "[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]"_SN
		+ "[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]"_SN
		+ "[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]"_SN
		+ "[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]"_SN
		+ "[7,[5,[[3,8],[1,4]]]]"_SN
		+ "[[2,[2,2]],[8,[8,1]]]"_SN
		+ "[2,9]"_SN
		+ "[1,[[[9,3],9],[[9,0],[0,7]]]]"_SN
		+ "[[[5,[7,4]],7],1]"_SN
		+ "[[[[4,2],2],6],[8,7]]"_SN,
		"[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]"_SN
	);
}

TEST(Day18, ExampleMaginitude)
{
	EXPECT_EQ("[[1,2],[[3,4],5]]"_SN.Magnitude(), 143);
	EXPECT_EQ("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]"_SN.Magnitude(), 1384);
	EXPECT_EQ("[[[[1,1],[2,2]],[3,3]],[4,4]]"_SN.Magnitude(), 445);
	EXPECT_EQ("[[[[3,0],[5,3]],[4,4]],[5,5]]"_SN.Magnitude(), 791);
	EXPECT_EQ("[[[[5,0],[7,4]],[5,5]],[6,6]]"_SN.Magnitude(), 1137);
	EXPECT_EQ("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]"_SN.Magnitude(), 3488);
}

TEST(Day18, FinalExample)
{
	EXPECT_EQ(
		"[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]"_SN
		+ "[[[5,[2,8]],4],[5,[[9,9],0]]]"_SN
		+ "[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]"_SN
		+ "[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]"_SN
		+ "[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]"_SN
		+ "[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]"_SN
		+ "[[[[5,4],[7,7]],8],[[8,3],8]]"_SN
		+ "[[9,3],[[9,9],[6,[4,9]]]]"_SN
		+ "[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]"_SN
		+ "[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"_SN,
		"[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]"_SN);

	EXPECT_EQ("[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]"_SN.Magnitude(), 4140);
}
