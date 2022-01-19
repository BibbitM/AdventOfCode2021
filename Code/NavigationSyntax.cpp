#include "pch.h"
#include "NavigationSyntax.h"

#include <vector>

int64_t NavigationSyntax::GetCompletionScore(std::string_view completionLine)
{
	int64_t score = 0;
	for (char c : completionLine)
		score = score * 5 + GetCompletionScore(c);
	return score;
}

char NavigationSyntax::FindChunkError(std::string_view line)
{
	std::vector<char> openedStack;
	openedStack.reserve(line.length());

	for (const char c : line)
	{
		if (IsChunkOpening(c))
			openedStack.push_back(c);
		else
		{
			if (openedStack.empty())
				return c;
			if (openedStack.back() != GetPaired(c))
				return c;
			openedStack.pop_back();
		}
	}

	return '\0';
}

std::string NavigationSyntax::DetermineLineCompletion(std::string_view line)
{
	std::vector<char> openedStack;
	openedStack.reserve(line.length());

	for (const char c : line)
	{
		if (IsChunkOpening(c))
			openedStack.push_back(c);
		else
		{
			if (openedStack.empty())
				return {};
			if (openedStack.back() != GetPaired(c))
				return {};
			openedStack.pop_back();
		}
	}

	std::string completion;
	completion.reserve(openedStack.size());
	for (auto it = openedStack.crbegin(); it != openedStack.crend(); ++it)
		completion.push_back(GetPaired(*it));
	return completion;
}
