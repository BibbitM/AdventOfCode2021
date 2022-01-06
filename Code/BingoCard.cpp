#include "pch.h"

#include "BingoCard.h"

void BingoCard::AddBoard(const BingoBoard& bingoBoard)
{
	m_boards.push_back(bingoBoard);
}

int BingoCard::Play(const std::vector<int>& numbers)
{
	for (int num : numbers)
	{
		for(BingoBoard& board : m_boards)
		{
			if (board.Match(num))
				return num * board.SumOfUnmatched();
		}
	}
	return INVALID_POINTS;
}