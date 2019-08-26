#include "Settings.h"

#include "RayCaster.h"

#include "application/Application.h"
#include "map/Map.h"

namespace Labyrinth
{
	Ray RayCaster::Cast(glm::vec2 position, float angle)
	{
		RayDirection direction = RayCaster::_GetRayDirection(angle);

		RayHit horizontalCollision = RayCaster::_ScanHorizontal(position, angle, direction);
		RayHit verticalCollision = RayCaster::_ScanVertical(position, angle, direction);

		Ray ray;
		ray.TextureXOffset = 0.0f;
		ray.WallType = MapTileType::None;

		if (horizontalCollision.Distance < verticalCollision.Distance)
		{
			ray.Distance = horizontalCollision.Distance;
			ray.TextureXOffset = horizontalCollision.TextureXOffset;
			ray.WallType = horizontalCollision.WallType;

			if (direction == RayDirection::UpRight || direction == RayDirection::UpLeft)
			{
				ray.Type = RayCollisionType::Top;
			}
			else
			{
				ray.Type = RayCollisionType::Bottom;
			}
		}
		else
		{
			ray.Distance = verticalCollision.Distance;
			ray.TextureXOffset = verticalCollision.TextureXOffset;
			ray.WallType = verticalCollision.WallType;

			if (direction == RayDirection::UpRight || direction == RayDirection::DownRight)
			{
				ray.Type = RayCollisionType::Right;
			}
			else
			{
				ray.Type = RayCollisionType::Left;
			}
		}

		return ray;
	}

	RayDirection RayCaster::_GetRayDirection(float angle)
	{
		float cappedAngle = fmod(angle, 360.0f);
		if (cappedAngle < 0)
		{
			cappedAngle += 360.0f;
		}

		// Facing Up
		if (cappedAngle > 180)
		{
			// Facing Right
			if ((cappedAngle < 90) || (cappedAngle > 270))
			{
				return RayDirection::UpRight;
			}
			// Facing Left
			else
			{
				return RayDirection::UpLeft;
			}
		}
		// Facing Down
		else
		{
			// Facing Right
			if ((cappedAngle < 90) || (cappedAngle > 270))
			{
				return RayDirection::DownRight;
			}
			// Facing Left
			else
			{
				return RayDirection::DownLeft;
			}
		}
	}

	// TODO: Allow to check for different tile types
	RayHit RayCaster::_ScanHorizontal(glm::vec2 position, float angle, RayDirection direction)
	{
		RayHit hit;

		float angleRadians = glm::radians(angle);

		Map& map = Application::MainScene().GetMap();

		float tileSize = (float)WALL_SIZE;

		// Horizontal intersection always on grid boundry
		float yIntercept = floor(position.y / tileSize) * tileSize;

		// If facing down must add another tile, to get to next row down
		if (direction == RayDirection::DownRight || direction == RayDirection::DownLeft)
		{
			yIntercept += tileSize;
		}

		// Find X intercept using horizontal intersection and angle
		float xIntercept = position.x + ((yIntercept - position.y) / glm::tan(angleRadians));

		// Y Step is always on grid boundry
		float yStep = tileSize;
		float yOffset = 1.0f; // Makes sure tests are run in a single cell on either side of border

		// Decrease Y position if ray facing up
		if (direction == RayDirection::UpRight || direction == RayDirection::UpLeft)
		{
			yOffset = -1.0f;

			// Ensure negative
			if (yStep > 0)
			{
				yStep *= -1.0f;
			}
		}
		else
		{
			// Ensure positive
			if (yStep < 0)
			{
				yStep *= -1.0f;
			}
		}

		// Find X step by using Y step and angle
		float xStep = tileSize / glm::tan(angleRadians);

		// Decrease X position if ray facing left
		if (direction == RayDirection::UpLeft || direction == RayDirection::DownLeft)
		{
			if (xStep > 0)
			{
				xStep *= -1.0f;
			}
		}
		else
		{
			// Ensure positive
			if (xStep < 0)
			{
				xStep *= -1.0f;
			}
		}

		// Iterate through tiles until collision or end of map
		float nextX = xIntercept;
		float nextY = yIntercept;

		while (nextX > 0.0f && nextX < map.GetWidth() && (nextY + yOffset) > 0.0f && (nextY + yOffset) < map.GetHeight())
		{
			MapTileType tileType = map.TileAtGridCoordinate(nextX, (nextY + yOffset));

			if (tileType != MapTileType::None)
			{
				// Collision found, return length of ray
				float xLength = position.x - nextX;
				float yLength = position.y - nextY;

				hit.Distance = sqrt(xLength * xLength + yLength * yLength);
				hit.TextureXOffset = fmod(nextX, tileSize);
				hit.WallType = tileType;

				if (hit.TextureXOffset < 0)
				{
					hit.TextureXOffset += tileSize;
				}

				return hit;
			}

			nextX += xStep;
			nextY += yStep;
		}

		float distance = 999999.9f;

		hit.Distance = distance;
		hit.TextureXOffset = 0;

		return hit;
	}

	RayHit RayCaster::_ScanVertical(glm::vec2 position, float angle, RayDirection direction)
	{
		RayHit hit;

		float angleRadians = glm::radians(angle);

		Map& map = Application::MainScene().GetMap();

		float tileSize = (float)WALL_SIZE;

		// Vertical intersection always on grid boundry
		float xIntercept = floor(position.x / tileSize) * tileSize;

		// If facing right must add another tile, to get to next column over
		if (direction == RayDirection::UpRight || direction == RayDirection::DownRight)
		{
			xIntercept += tileSize;
		}

		// Find Y intercept using horizontal intersection and angle
		float yIntercept = position.y + ((xIntercept - position.x) * glm::tan(angleRadians));

		// X Step is always on grid boundry
		float xStep = tileSize;
		float xOffset = 1.0f; // Makes sure tests are run in a single cell on either side of border

		// Decrease X position if ray facing left
		if (direction == RayDirection::UpLeft || direction == RayDirection::DownLeft)
		{
			xOffset = -1.0f;

			// Ensure negative
			if (xStep > 0)
			{
				xStep *= -1.0f;
			}
		}
		else
		{
			// Ensure positive
			if (xStep < 0)
			{
				xStep *= -1.0f;
			}
		}

		// Find Y step by using X step and angle
		float yStep = tileSize * glm::tan(angleRadians);

		// Decrease Y position if ray facing up
		if (direction == RayDirection::UpRight || direction == RayDirection::UpLeft)
		{
			// Ensure negative
			if (yStep > 0)
			{
				yStep *= -1.0f;
			}
		}
		else
		{
			// Ensure positive
			if (yStep < 0)
			{
				yStep *= -1.0f;
			}
		}

		// Iterate through tiles until collision or end of map
		float nextX = xIntercept;
		float nextY = yIntercept;

		while ((nextX + xOffset) > 0.0f && (nextX + xOffset) < map.GetWidth() && nextY > 0.0f && nextY < map.GetHeight())
		{
			MapTileType tileType = map.TileAtGridCoordinate((nextX + xOffset), nextY);

			if (tileType != MapTileType::None)
			{
				// Collision found, return length of ray
				float xLength = position.x - nextX;
				float yLength = position.y - nextY;

				hit.Distance = sqrt(xLength * xLength + yLength * yLength);
				hit.TextureXOffset = fmod(nextY, tileSize);
				hit.WallType = tileType;

				if (hit.TextureXOffset < 0)
				{
					hit.TextureXOffset += tileSize;
				}

				return hit;
			}

			nextX += xStep;
			nextY += yStep;
		}

		float distance = 999999.9f;

		hit.Distance = distance;
		hit.TextureXOffset = 0;

		return hit;
	}
}
