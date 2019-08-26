#pragma once

#include "map/Map.h"

#include <glm/glm.hpp>

namespace Labyrinth
{
	enum class RayDirection
	{
		UpRight = 0, UpLeft, DownRight, DownLeft
	};

	enum class RayCollisionType
	{
		None = 0, Top, Bottom, Left, Right
	};

	struct Ray
	{
		RayCollisionType Type;
		float Distance;
		float TextureXOffset;
		MapTileType WallType;
	};

	struct RayHit
	{
		float Distance;
		float TextureXOffset;
		MapTileType WallType;
	};

	class RayCaster
	{
	public:
		static Ray Cast(glm::vec2 position, float angle);

	private:
		static RayDirection _GetRayDirection(float angle);
		static RayHit _ScanHorizontal(glm::vec2 position, float angle, RayDirection direction);
		static RayHit _ScanVertical(glm::vec2 position, float angle, RayDirection direction);

	};
}
