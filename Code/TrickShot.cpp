#include "pch.h"
#include "TrickShot.h"

std::istream& operator>>(std::istream& in, TrickShot::TargetArea& area)
{
	int minX, maxX, minY, maxY;

	in.ignore(15); //< "target area: x="
	in >> minX;
	in.ignore(2); //< ".."
	in >> maxX;
	in.ignore(4); //< ", y="
	in >> minY;
	in.ignore(2); //< ".."
	in >> maxY;

	area = TrickShot::TargetArea{ { minX, minY }, { maxX, maxY } };

	return in;
}

std::vector<int> TrickShot::GetXForces(const TargetArea& area)
{
	std::vector<int> forces;

	for (int x = 0; x <= area.GetMax().x; ++x)
	{
		int targetX = 0;
		int stepX = x;
		while (stepX == 0 && targetX >= area.GetMin().x && targetX <= area.GetMax().x || stepX > 0 && targetX <= area.GetMax().x)
		{
			targetX += stepX;
			stepX = std::max(stepX - 1, 0);
			if (targetX >= area.GetMin().x && targetX <= area.GetMax().x)
			{
				forces.push_back(x);
				break;
			}
		}
	}

	return forces;
}

std::vector<int> TrickShot::GetYForces(const TargetArea& area)
{
	std::vector<int> forces;

	const int maxY = std::max(std::abs(area.GetMin().y), std::abs(area.GetMax().y));

	for (int y = -maxY; y <= maxY; ++y)
	{
		int targetY = 0;
		int stepY = y;
		while (stepY > 0 || targetY >= area.GetMin().y)
		{
			targetY += stepY;
			stepY -= 1;
			if (targetY >= area.GetMin().y && targetY <= area.GetMax().y)
			{
				forces.push_back(y);
				break;
			}
		}
	}

	return forces;
}

bool TrickShot::SimuleteShot(const IntVector2& shot, const TargetArea& area)
{
	int stepY = shot.y;
	int stepX = shot.x;
	IntVector2 target{};

	while ((stepY > 0 || target.y >= area.GetMin().y)
		&& (stepX == 0 && target.x >= area.GetMin().x && target.x <= area.GetMax().x || stepX > 0 && target.x <= area.GetMax().x))
	{
		target.x += stepX;
		target.y += stepY;
		stepX = std::max(stepX - 1, 0);
		stepY -= 1;
		if (target.x >= area.GetMin().x && target.x <= area.GetMax().x &&
			target.y >= area.GetMin().y && target.y <= area.GetMax().y)
		{
			return true;
		}
	}

	return false;
}

std::vector<IntVector2> TrickShot::FindAllShots(const TargetArea& area)
{
	std::vector<IntVector2> allShots{};

	std::vector<int> forcesX = GetXForces(area);
	std::vector<int> forcesY = GetYForces(area);

	for (int y : forcesY)
	{
		for (int x : forcesX)
		{
			IntVector2 shot{ x, y };

			if (SimuleteShot(shot, area))
				allShots.push_back(shot);
		}
	}

	return allShots;
}

IntVector2 TrickShot::FindHighestShot(const TargetArea& area)
{
	std::vector<IntVector2> allShots = FindAllShots(area);
	if (allShots.empty())
		return IntVector2{ -1, -1 };
	return allShots.back();
}

int TrickShot::GetHighestPosition(int shotY)
{
	return shotY > 0 ? shotY * (shotY + 1) / 2 : shotY;
}
