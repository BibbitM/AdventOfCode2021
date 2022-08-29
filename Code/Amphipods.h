#pragma once

#include <array>
#include <string_view>

namespace Amphipods
{
	constexpr size_t c_sideRoomSize = 2;
	constexpr size_t c_sideRoomsCount = 4;

	constexpr std::array<char, c_sideRoomsCount> c_expectedTypeInRoom = { 'A', 'B', 'C', 'D' };

	using SideRoom = std::array<char, c_sideRoomSize>;

	class Burrow
	{
	public:
		Burrow();
		Burrow(std::string_view amphipods);

		bool IsOrganized() const;

	private:
		std::array<SideRoom, c_sideRoomsCount> m_sideRooms;
	};
}
