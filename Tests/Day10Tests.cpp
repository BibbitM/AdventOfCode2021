#include "pch.h"

#include "../Code/NavigationSyntax.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace
{
	constexpr const char c_exampleInput[] = R"--([({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]])--";
}

TEST(Day10, IsChunkOpeningBrackets)
{
	EXPECT_TRUE(NavigationSyntax::IsChunkOpening('('));
	EXPECT_TRUE(NavigationSyntax::IsChunkOpening('['));
	EXPECT_TRUE(NavigationSyntax::IsChunkOpening('{'));
	EXPECT_TRUE(NavigationSyntax::IsChunkOpening('<'));

	EXPECT_FALSE(NavigationSyntax::IsChunkOpening(')'));
	EXPECT_FALSE(NavigationSyntax::IsChunkOpening(']'));
	EXPECT_FALSE(NavigationSyntax::IsChunkOpening('}'));
	EXPECT_FALSE(NavigationSyntax::IsChunkOpening('>'));
}

TEST(Day10, IsChunkClosingBrackets)
{
	EXPECT_TRUE(NavigationSyntax::IsChunkClosing(')'));
	EXPECT_TRUE(NavigationSyntax::IsChunkClosing(']'));
	EXPECT_TRUE(NavigationSyntax::IsChunkClosing('}'));
	EXPECT_TRUE(NavigationSyntax::IsChunkClosing('>'));

	EXPECT_FALSE(NavigationSyntax::IsChunkClosing('('));
	EXPECT_FALSE(NavigationSyntax::IsChunkClosing('['));
	EXPECT_FALSE(NavigationSyntax::IsChunkClosing('{'));
	EXPECT_FALSE(NavigationSyntax::IsChunkClosing('<'));
}

TEST(Day10, GetPairedBrackets)
{
	EXPECT_EQ(NavigationSyntax::GetPaired('('), ')');
	EXPECT_EQ(NavigationSyntax::GetPaired('['), ']');
	EXPECT_EQ(NavigationSyntax::GetPaired('{'), '}');
	EXPECT_EQ(NavigationSyntax::GetPaired('<'), '>');

	EXPECT_EQ(NavigationSyntax::GetPaired(')'), '(');
	EXPECT_EQ(NavigationSyntax::GetPaired(']'), '[');
	EXPECT_EQ(NavigationSyntax::GetPaired('}'), '{');
	EXPECT_EQ(NavigationSyntax::GetPaired('>'), '<');
}

TEST(Day10, GetErrorScoreZero)
{
	EXPECT_EQ(NavigationSyntax::GetErrorScore('\0'), 0);
}

TEST(Day10, GetErrorScoreBrackets)
{
	EXPECT_EQ(NavigationSyntax::GetErrorScore(')'), 3);
	EXPECT_EQ(NavigationSyntax::GetErrorScore(']'), 57);
	EXPECT_EQ(NavigationSyntax::GetErrorScore('}'), 1197);
	EXPECT_EQ(NavigationSyntax::GetErrorScore('>'), 25137);
}

TEST(Day10, FindChunkErrorEmpty)
{
	EXPECT_EQ(NavigationSyntax::FindChunkError(""), '\0');
}

TEST(Day10, FindChunkErrorSimple)
{
	EXPECT_EQ(NavigationSyntax::FindChunkError("[)"), ')');
	EXPECT_EQ(NavigationSyntax::FindChunkError("}"), '}');
	EXPECT_EQ(NavigationSyntax::FindChunkError("<<{}>]"), ']');
	EXPECT_EQ(NavigationSyntax::FindChunkError("<<{}>>>"), '>');
}

TEST(Day10, FindChunkErrorExample)
{
	EXPECT_EQ(NavigationSyntax::FindChunkError("{([(<{}[<>[]}>{[]{[(<()>"), '}');
	EXPECT_EQ(NavigationSyntax::FindChunkError("[[<[([]))<([[{}[[()]]]"), ')');
	EXPECT_EQ(NavigationSyntax::FindChunkError("[{[{({}]{}}([{[{{{}}([]"), ']');
	EXPECT_EQ(NavigationSyntax::FindChunkError("[<(<(<(<{}))><([]([]()"), ')');
	EXPECT_EQ(NavigationSyntax::FindChunkError("<{([([[(<>()){}]>(<<{{"), '>');
}

TEST(Day10, CalculateTotalSyntaxErrorScoreExample)
{
	std::istringstream input(c_exampleInput);

	int totalErrorScore = 0;
	std::string line;
	while (std::getline(input, line))
	{
		totalErrorScore += NavigationSyntax::GetErrorScore(NavigationSyntax::FindChunkError(line));
	}

	EXPECT_EQ(totalErrorScore, 26397);
}

TEST(Day10, DetermineLineCompletionEmpty)
{
	EXPECT_TRUE(NavigationSyntax::DetermineLineCompletion("").empty());
}

TEST(Day10, DetermineLineCompletionProperMessage)
{
	EXPECT_TRUE(NavigationSyntax::DetermineLineCompletion("()").empty());
	EXPECT_TRUE(NavigationSyntax::DetermineLineCompletion("([{}<>])").empty());
}

TEST(Day10, DetermineLineCompletionErrorMessage)
{
	EXPECT_TRUE(NavigationSyntax::DetermineLineCompletion("(>").empty());
	EXPECT_TRUE(NavigationSyntax::DetermineLineCompletion("([{}<)").empty());
}

TEST(Day10, DetermineLineCompletionSimple)
{
	EXPECT_EQ(NavigationSyntax::DetermineLineCompletion("("), ")");
	EXPECT_EQ(NavigationSyntax::DetermineLineCompletion("([{<"), ">}])");
}

TEST(Day10, DetermineLineCompletionExample)
{
	EXPECT_EQ(NavigationSyntax::DetermineLineCompletion("[({(<(())[]>[[{[]{<()<>>"), "}}]])})]");
	EXPECT_EQ(NavigationSyntax::DetermineLineCompletion("[(()[<>])]({[<{<<[]>>("), ")}>]})");
	EXPECT_EQ(NavigationSyntax::DetermineLineCompletion("(((({<>}<{<{<>}{[]{[]{}"), "}}>}>))))");
	EXPECT_EQ(NavigationSyntax::DetermineLineCompletion("{<[[]]>}<{[{[{[]{()[[[]"), "]]}}]}]}>");
	EXPECT_EQ(NavigationSyntax::DetermineLineCompletion("<{([{{}}[<[[[<>{}]]]>[]]"), "])}>");
}

TEST(Day10, GetCompletionScoreZero)
{
	EXPECT_EQ(NavigationSyntax::GetCompletionScore('\0'), 0);
}

TEST(Day10, GetCompletionScoreBrackets)
{
	EXPECT_EQ(NavigationSyntax::GetCompletionScore(')'), 1);
	EXPECT_EQ(NavigationSyntax::GetCompletionScore(']'), 2);
	EXPECT_EQ(NavigationSyntax::GetCompletionScore('}'), 3);
	EXPECT_EQ(NavigationSyntax::GetCompletionScore('>'), 4);
}

TEST(Day10, GetCompletionScoreSimple)
{
	EXPECT_EQ(NavigationSyntax::GetCompletionScore("])}>"), 294);
}

TEST(Day10, GetCompletionScoreExample)
{
	EXPECT_EQ(NavigationSyntax::GetCompletionScore("}}]])})]"), 288957);
	EXPECT_EQ(NavigationSyntax::GetCompletionScore(")}>]})"), 5566);
	EXPECT_EQ(NavigationSyntax::GetCompletionScore("}}>}>))))"), 1480781);
	EXPECT_EQ(NavigationSyntax::GetCompletionScore("]]}}]}]}>"), 995444);
	EXPECT_EQ(NavigationSyntax::GetCompletionScore("])}>"), 294);
}

TEST(Day10, CalculateMiddleCompletionScoreExample)
{
	std::istringstream input(c_exampleInput);

	std::vector<int64_t> completionScores;
	std::string line;
	while (std::getline(input, line))
	{
		std::string completionLine = NavigationSyntax::DetermineLineCompletion(line);
		if (!completionLine.empty())
			completionScores.push_back(NavigationSyntax::GetCompletionScore(completionLine));
	}

	int64_t middleCompletionScore = 0;
	if (!completionScores.empty())
	{
		std::sort(completionScores.begin(), completionScores.end());
		middleCompletionScore = completionScores[completionScores.size() / 2];
	}
	EXPECT_EQ(middleCompletionScore, 288957);
}
