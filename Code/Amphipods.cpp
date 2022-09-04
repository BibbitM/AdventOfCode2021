#include "pch.h"
#include "Amphipods.h"

#include "HashBytes.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

Amphipods::Burrow::Burrow()
	: m_sideRooms{ SideRoom{ 'A', 'A', 'A', 'A' }, SideRoom{ 'B', 'B', 'B', 'B' }, SideRoom{ 'C', 'C', 'C', 'C' }, SideRoom{ 'D', 'D', 'D', 'D' } }
	, m_hallway{}
{
}

void Amphipods::Burrow::Unfold()
{
	m_sideRooms[0][3] = m_sideRooms[0][1];
	m_sideRooms[1][3] = m_sideRooms[1][1];
	m_sideRooms[2][3] = m_sideRooms[2][1];
	m_sideRooms[3][3] = m_sideRooms[3][1];

	m_sideRooms[0][1] = 'D';
	m_sideRooms[1][1] = 'C';
	m_sideRooms[2][1] = 'B';
	m_sideRooms[3][1] = 'A';

	m_sideRooms[0][2] = 'D';
	m_sideRooms[1][2] = 'B';
	m_sideRooms[2][2] = 'A';
	m_sideRooms[3][2] = 'C';
}

Amphipods::Burrow::Burrow(std::string_view amphipods)
	: Burrow()
{
	size_t maxCount = std::min(c_sideRoomsCount * c_sideRoomSize, amphipods.size());
	for (size_t i = 0; i < maxCount; ++i)
	{
		const size_t room = i % c_sideRoomsCount;
		const size_t idx = i / c_sideRoomsCount;

		m_sideRooms[room][idx] = amphipods[i];
	}
}

bool Amphipods::Burrow::IsOrganized() const
{
	for (size_t room = 0; room < c_sideRoomsCount; ++room)
	{
		for (size_t row = 0; row < c_sideRoomSize; ++row)
		{
			if (m_sideRooms[room][row] != c_expectedTypeInRoom[room])
			{
				return false;
			}
		}
	}

	return true;
}

int Amphipods::Burrow::MoveToHallway(size_t room, size_t hallwayPos)
{
	size_t row = std::numeric_limits<size_t>::max();
	char amphipod = '\0';
	for (size_t r = 0; r < c_sideRoomSize; ++r)
	{
		if (m_sideRooms[room][r] != '\0')
		{
			amphipod = m_sideRooms[room][r];
			row = r;
			break;
		}
	}

	if (amphipod == '\0')
	{
		return 0;
	}

	if (amphipod == c_expectedTypeInRoom[room])
	{
		bool allExpected = true;
		for (size_t r = row + 1; r < c_sideRoomSize; ++r)
		{
			if (m_sideRooms[room][r] != amphipod)
			{
				allExpected = false;
				break;
			}
		}

		if (allExpected)
		{
			return 0;
		}
	}

	if (std::find(c_roomPositionInHallway.begin(), c_roomPositionInHallway.end(), hallwayPos) != c_roomPositionInHallway.end())
	{
		return 0;
	}

	const size_t roomPos = c_roomPositionInHallway[room];
	for (size_t i = std::min(roomPos, hallwayPos), last = std::max(roomPos, hallwayPos); i <= last; ++i)
	{
		if (m_hallway[i] != '\0')
		{
			return 0;
		}
	}

	m_sideRooms[room][row] = '\0';
	m_hallway[hallwayPos] = amphipod;

	const int numOfSteps = std::abs(static_cast<int>(hallwayPos) - static_cast<int>(roomPos)) + static_cast<int>(row + 1);
	return numOfSteps * GetEnergyPerStep(amphipod);
}

int Amphipods::Burrow::MoveToRoom(size_t hallwayPos, size_t room)
{
	const char amphipod = m_hallway[hallwayPos];
	if (c_expectedTypeInRoom[room] != amphipod)
	{
		return 0;
	}

	size_t row = 0;
	for (size_t r = c_sideRoomSize; r > 0; --r)
	{
		row = r - 1;
		if (m_sideRooms[room][row] == '\0')
		{
			break;
		}
		if (m_sideRooms[room][row] != amphipod)
		{
			return 0;
		}
	}

	const size_t roomPos = c_roomPositionInHallway[room];
	for (size_t i = std::min(roomPos, hallwayPos + 1), last = std::max(roomPos + 1, hallwayPos) - 1; i <= last; ++i)
	{
		if (m_hallway[i] != '\0')
		{
			return 0;
		}
	}

	const int numOfSteps = std::abs(static_cast<int>(hallwayPos) - static_cast<int>(roomPos)) + static_cast<int>(row + 1);

	m_hallway[hallwayPos] = '\0';
	m_sideRooms[room][row] = amphipod;

	return numOfSteps * GetEnergyPerStep(amphipod);
}

int Amphipods::Burrow::CalculateOrganizationCost() const
{
	int lowestOrganizationCost = std::numeric_limits<int>::max();
	std::unordered_map<Burrow, int> checkedBurrows{};
	CalculateOrganizationCostRecursively(0, checkedBurrows, lowestOrganizationCost);
	return lowestOrganizationCost;
}

void Amphipods::Burrow::CalculateOrganizationCostRecursively(int organizationCost, std::unordered_map<Burrow, int>& checkedBurrows, int& lowestOrganizationCost) const
{
	if (IsOrganized())
	{
		if (organizationCost < lowestOrganizationCost)
		{
			lowestOrganizationCost = organizationCost;
		}
		return;
	}

	if (organizationCost >= lowestOrganizationCost)
	{
		return;
	}

	auto insertResult = checkedBurrows.insert(std::make_pair(*this, organizationCost));
	if (!insertResult.second)
	{
		if (insertResult.first->second <= organizationCost)
		{
			return;
		}
		else
		{
			insertResult.first->second = organizationCost;
		}
	}

	// Try all possible moves from rooms to hallway.
	for (size_t roomIdx = 0; roomIdx < c_sideRoomsCount; ++roomIdx)
	{
		for (size_t hallwayIdx = 0; hallwayIdx < c_hallwayLength; ++hallwayIdx)
		{
			Burrow burrowCopy{ *this };
			const int moveCost = burrowCopy.MoveToHallway(roomIdx, hallwayIdx);
			if (moveCost)
			{
				burrowCopy.CalculateOrganizationCostRecursively(organizationCost + moveCost, checkedBurrows, lowestOrganizationCost);
			}
		}

	}

	// Try all possible moves from hallway to room.
	for (size_t hallwayIdx = 0; hallwayIdx < c_hallwayLength; ++hallwayIdx)
	{
		for (size_t roomIdx = 0; roomIdx < c_sideRoomsCount; ++roomIdx)
		{
			Burrow burrowCopy{ *this };
			const int moveCost = burrowCopy.MoveToRoom(hallwayIdx, roomIdx);
			if (moveCost)
			{
				burrowCopy.CalculateOrganizationCostRecursively(organizationCost + moveCost, checkedBurrows, lowestOrganizationCost);
			}
		}
	}
}

size_t Amphipods::Burrow::CalculateHash() const
{
	return hash_bytes(this, sizeof(*this));
}

namespace Amphipods
{
	std::istream& operator>>(std::istream& in, Burrow& burrow)
	{
		/*
		#############
		#...........#
		###B#C#B#D###
		  #A#D#C#A#
		  #########
		*/
		in.ignore(31);
		in >> burrow.m_sideRooms[0][0];
		in.ignore(1);
		in >> burrow.m_sideRooms[1][0];
		in.ignore(1);
		in >> burrow.m_sideRooms[2][0];
		in.ignore(1);
		in >> burrow.m_sideRooms[3][0];
		in.ignore(7);
		in >> burrow.m_sideRooms[0][1];
		in.ignore(1);
		in >> burrow.m_sideRooms[1][1];
		in.ignore(1);
		in >> burrow.m_sideRooms[2][1];
		in.ignore(1);
		in >> burrow.m_sideRooms[3][1];
		in.ignore(13);
		return in;
	}
}
