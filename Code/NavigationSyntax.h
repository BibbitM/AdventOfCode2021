#pragma once

#include <limits>
#include <string>
#include <string_view>

class NavigationSyntax
{
public:
	static constexpr const char c_openingChars[] = { '(', '[', '{', '<' };
	static constexpr const char c_closingChars[] = { ')', ']', '}', '>' };
	static constexpr const int c_errorScores[] = { 3, 57, 1197, 25137 };

	static constexpr size_t npos = std::numeric_limits<size_t>::max();

	static constexpr size_t GetIndex(const char(&chars)[4], char c)
	{
		for (size_t i = 0; i < 4; ++i)
			if (chars[i] == c)
				return i;
		return npos;
	}

	static bool IsChunkOpening(char c)
	{
		return GetIndex(c_openingChars, c) != npos;
	}

	static bool IsChunkClosing(char c)
	{
		return GetIndex(c_closingChars, c) != npos;
	}

	static char GetPaired(char c)
	{ 
		const size_t openingIdx = GetIndex(c_openingChars, c);
		if (openingIdx != npos)
			return c_closingChars[openingIdx];

		const size_t closingIdx = GetIndex(c_closingChars, c);
		if (closingIdx != npos)
			return c_openingChars[closingIdx];

		return '\0';
	}

	static int GetErrorScore(char c)
	{
		const size_t closingIdx = GetIndex(c_closingChars, c);
		if (closingIdx != npos)
			return c_errorScores[closingIdx];
		return 0;
	}

	static int GetCompletionScore(char c)
	{
		return static_cast<int>(GetIndex(c_closingChars, c) + 1);
	}

	static int64_t GetCompletionScore(std::string_view completionLine);

	static char FindChunkError(std::string_view line);
	static std::string DetermineLineCompletion(std::string_view line);
};

