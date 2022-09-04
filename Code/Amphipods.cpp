#include "pch.h"
#include "Amphipods.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

Amphipods::Burrow::Burrow()
	: m_sideRooms{ SideRoom{ 'A', 'A' }, SideRoom{ 'B', 'B' }, SideRoom{ 'C', 'C' }, SideRoom{ 'D', 'D' } }
	, m_hallway{}
{
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
		if (m_sideRooms[room][0] != m_sideRooms[room][1] ||
			m_sideRooms[room][0] != c_expectedTypeInRoom[room])
		{
			return false;
		}
	}

	return true;
}

int Amphipods::Burrow::MoveToHallway(size_t room, size_t hallwayPos)
{
	bool isSecondRow = false;
	char amphipod = m_sideRooms[room][0];
	if (!amphipod)
	{
		isSecondRow = true;
		amphipod = m_sideRooms[room][1];
		if (amphipod == c_expectedTypeInRoom[room])
		{
			return 0;
		}
	}
	else
	{
		if (amphipod == m_sideRooms[room][1] && amphipod == c_expectedTypeInRoom[room])
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

	m_sideRooms[room][isSecondRow ? 1 : 0] = '\0';
	m_hallway[hallwayPos] = amphipod;

	const int numOfSteps = std::abs(static_cast<int>(hallwayPos) - static_cast<int>(roomPos)) + (isSecondRow ? 2 : 1);
	return numOfSteps * GetEnergyPerStep(amphipod);
}

int Amphipods::Burrow::MoveToRoom(size_t hallwayPos, size_t room)
{
	if (m_sideRooms[room][0] != '\0')
	{
		return 0;
	}

	const char amphipod = m_hallway[hallwayPos];
	if (c_expectedTypeInRoom[room] != amphipod)
	{
		return 0;
	}

	bool isSecondRow = m_sideRooms[room][1] == '\0';
	if (!isSecondRow && m_sideRooms[room][1] != amphipod)
	{
		return 0;
	}

	const size_t roomPos = c_roomPositionInHallway[room];
	for (size_t i = std::min(roomPos, hallwayPos + 1), last = std::max(roomPos + 1, hallwayPos) - 1; i <= last; ++i)
	{
		if (m_hallway[i] != '\0')
		{
			return 0;
		}
	}

	const int numOfSteps = std::abs(static_cast<int>(hallwayPos) - static_cast<int>(roomPos)) + (isSecondRow ? 2 : 1);

	m_hallway[hallwayPos] = '\0';
	m_sideRooms[room][isSecondRow ? 1 : 0] = amphipod;

	return numOfSteps * GetEnergyPerStep(amphipod);
}

int Amphipods::Burrow::CalculateOrganizationCost() const
{
	int lowestOrganizationCost = std::numeric_limits<int>::max();
	CalculateOrganizationCostRecursively(0, lowestOrganizationCost);
	return lowestOrganizationCost;
}

void Amphipods::Burrow::CalculateOrganizationCostRecursively(int organizationCost, int& lowestOrganizationCost) const
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

	// Try all possible moves from rooms to hallway.
	for (size_t roomIdx = 0; roomIdx < c_sideRoomsCount; ++roomIdx)
	{
		for (size_t hallwayIdx = 0; hallwayIdx < c_hallwayLength; ++hallwayIdx)
		{
			Burrow burrowCopy{ *this };
			const int moveCost = burrowCopy.MoveToHallway(roomIdx, hallwayIdx);
			if (moveCost)
			{
				burrowCopy.CalculateOrganizationCostRecursively(organizationCost + moveCost, lowestOrganizationCost);
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
				burrowCopy.CalculateOrganizationCostRecursively(organizationCost + moveCost, lowestOrganizationCost);
			}
		}
	}
}

size_t Amphipods::Burrow::CalculateHash() const
{
	size_t hash = 0;

	for (size_t hallwayIdx = 0; hallwayIdx < c_hallwayLength; ++hallwayIdx)
	{
		hash = hash * c_hashValuesCount + GetHashValue(m_hallway[hallwayIdx]);
	}

	for (size_t roomIdx = 0; roomIdx < c_sideRoomsCount; ++roomIdx)
	{
		for (size_t inRoomIdx = 0; inRoomIdx < c_sideRoomSize; ++inRoomIdx)
		{
			hash = hash * c_hashValuesCount + GetHashValue(m_sideRooms[roomIdx][inRoomIdx]);
		}
	}

	return hash;
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
