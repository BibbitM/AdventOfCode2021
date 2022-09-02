#include "pch.h"
#include "Amphipods.h"

#include <algorithm>
#include <cmath>
#include  <utility>

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
	if (std::find(c_roomPositionInHallway.begin(), c_roomPositionInHallway.end(), hallwayPos) != c_roomPositionInHallway.end())
	{
		return 0;
	}

	if (m_hallway[hallwayPos] != '\0')
	{
		return 0;
	}

	bool isSecondRow = false;
	char amphipod = std::exchange(m_sideRooms[room][0], '\0');
	if (!amphipod)
	{
		isSecondRow = true;
		amphipod = std::exchange(m_sideRooms[room][1], '\0');
	}

	m_hallway[hallwayPos] = amphipod;

	const int numOfSteps = std::abs(static_cast<int>(hallwayPos) - static_cast<int>(c_roomPositionInHallway[room])) + (isSecondRow ? 2 : 1);
	return numOfSteps * GetEnergyPerStep(amphipod);
}
