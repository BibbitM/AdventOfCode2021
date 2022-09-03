#pragma once

#include <array>
#include <string_view>

namespace Amphipods
{
	constexpr size_t c_sideRoomSize = 2;
	constexpr size_t c_sideRoomsCount = 4;
	constexpr size_t c_hallwayLength = 11;

	constexpr std::array<char, c_sideRoomsCount> c_expectedTypeInRoom = { 'A', 'B', 'C', 'D' };
	constexpr std::array<size_t, c_sideRoomsCount> c_roomPositionInHallway = { 2, 4, 6, 8 };

	using SideRoom = std::array<char, c_sideRoomSize>;

	constexpr int GetEnergyPerStep(char amphipod)
	{
		switch (amphipod)
		{
		case 'A': return 1;
		case 'B': return 10;
		case 'C': return 100;
		case 'D': return 1000;
		default:  return 0;
		}
	}

	class Burrow
	{
	public:
		Burrow();
		Burrow(std::string_view amphipods);

		bool operator==(const Burrow&) const = default;

		bool IsOrganized() const;
		int MoveToHallway(size_t room, size_t hallwayPos);
		int MoveToRoom(size_t hallwayPos, size_t room);

	private:
		std::array<char, c_hallwayLength> m_hallway;
		std::array<SideRoom, c_sideRoomsCount> m_sideRooms;
	};
}
