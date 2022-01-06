#pragma once

#include "Bingo.h"

#include <vector>

class BingoCard
{
public:
	static constexpr int INVALID_POINTS = -1;
	
	void AddBoard(const Bingo& bingoBoard);
	int Play(const std::vector<int>& numbers);

private:
	std::vector<Bingo> m_boards;
};
