#pragma once

#include "BingoBoard.h"

#include <vector>

class BingoCard
{
public:
	static constexpr int INVALID_POINTS = -1;
	
	void AddBoard(const BingoBoard& bingoBoard);
	int Play(const std::vector<int>& numbers);

private:
	std::vector<BingoBoard> m_boards;
};
