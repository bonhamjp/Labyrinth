#include "Settings.h"

#include "MazeGenerator.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <vector>

namespace Labyrinth
{
	enum class MazeCarveStatus
	{
		Restart = 0, Up, Down, Left, Right, Finish
	};

	void GenerateBorders(Map& map, unsigned int exitColumn)
	{
		// Top and bottom of map
		unsigned int lastRowIndex = map.GetRowCount() - 1;
		for (unsigned int i = 0; i < map.GetColumnCount(); i++)
		{
			if (i == exitColumn)
			{
				map.AddTile(0, i, MapTileType::Exit);
			}
			else
			{
				map.AddTile(0, i, MapTileType::Wall);
			}

			map.AddTile(lastRowIndex, i, MapTileType::Wall);
		}

		// Left and right side of map
		unsigned int lastColumnIndex = map.GetColumnCount() - 1;
		for (unsigned int i = 0; i < map.GetRowCount(); i++)
		{
			map.AddTile(i, 0, MapTileType::Wall);
			map.AddTile(i, lastColumnIndex, MapTileType::Wall);
		}
	}

	unsigned int CellSurroundingPaths(Map& map, unsigned int currentX, unsigned int currentY)
	{
		// Borders can only have one surrounding path
		if (currentX < 1 || currentX > map.GetColumnCount() - 2 || currentY < 1 || currentY > map.GetRowCount() - 2)
		{
			return 0;
		}

		unsigned int surroundingPaths = 0;

		// Check if top is a pathway
		if ((currentY - 1 > 0) && map.TileAtGridIndices(currentX, currentY - 1) == MapTileType::None)
		{
			surroundingPaths++;
		}

		// Check if bottom is a pathway
		if ((currentY + 1 < map.GetRowCount()) && map.TileAtGridIndices(currentX, currentY + 1) == MapTileType::None)
		{
			surroundingPaths++;
		}

		// Check if left is a pathway
		if ((currentX - 1 > 0) && map.TileAtGridIndices(currentX - 1, currentY) == MapTileType::None)
		{
			surroundingPaths++;
		}

		// Check if right is a pathway
		if ((currentX + 1 < map.GetColumnCount()) && map.TileAtGridIndices(currentX + 1, currentY) == MapTileType::None)
		{
			surroundingPaths++;
		}

		return surroundingPaths;
	}

	bool CanCarveCell(Map& map, unsigned int currentX, unsigned int currentY)
	{
		// Cannot carve through boundry walls
		if (currentX < 1 || currentX > map.GetColumnCount() - 2 || currentY < 1 || currentY > map.GetRowCount() - 2)
		{
			return false;
		}

		MapTileType tileType = map.TileAtGridIndices(currentX, currentY);

		// If cell is already carved, can be moved to
		if (tileType == MapTileType::None)
		{
			return true;
		}

		// Cannot carve exit
		if (tileType == MapTileType::Exit)
		{
			return false;
		}

		// Only occasionally allow three surrounding passages 
		unsigned int maxSurroundingWalls = 2 + (rand() % 32 == 0 ? 1 : 0);

		// Neighbors are not factoring in cell currently being checked
		unsigned int maxSurroundingWallsForNeighbors = maxSurroundingWalls - 1;

		// Self and surrounding cells can only have two connections each
		if (CellSurroundingPaths(map, currentX, currentY) <= maxSurroundingWalls &&
			CellSurroundingPaths(map, currentX, currentY - 1) <= maxSurroundingWallsForNeighbors &&
			CellSurroundingPaths(map, currentX, currentY + 1) <= maxSurroundingWallsForNeighbors &&
			CellSurroundingPaths(map, currentX - 1, currentY) <= maxSurroundingWallsForNeighbors &&
			CellSurroundingPaths(map, currentX + 1, currentY) <= maxSurroundingWallsForNeighbors)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CanCarveInDirection(Map& map, unsigned int currentX, unsigned int currentY, MazeCarveStatus status)
	{
		unsigned int nextX = 0;
		unsigned int nextY = 0;

		switch (status)
		{
		case MazeCarveStatus::Up:
			nextX = currentX;
			nextY = currentY - 1;

			return CanCarveCell(map, nextX, nextY);

			break;
		case MazeCarveStatus::Down:
			nextX = currentX;
			nextY = currentY + 1;

			return CanCarveCell(map, nextX, nextY);

			break;
		case MazeCarveStatus::Left:
			nextX = currentX - 1;
			nextY = currentY;

			return CanCarveCell(map, nextX, nextY);

			break;
		case MazeCarveStatus::Right:
			nextX = currentX + 1;
			nextY = currentY;

			return CanCarveCell(map, nextX, nextY);

			break;

		default:
			return false;
		}
	}

	MazeCarveStatus NextMazePosition(Map& map, unsigned int currentX, unsigned int currentY, unsigned int endX, unsigned int endY)
	{
		if ((currentX == endX && (currentY + 1) == endY) ||
			(currentX == (endX - 1) && currentY == endY) ||
			(currentX == (endX + 1) && currentY == endY))
		{
			return MazeCarveStatus::Finish;
		}

		// Randomly try each possible direction
		std::vector<MazeCarveStatus> directions{ MazeCarveStatus::Up, MazeCarveStatus::Down, MazeCarveStatus::Left, MazeCarveStatus::Right };

		while (directions.size() > 0)
		{
			unsigned int nextDirectionIndex = rand() % directions.size();
			MazeCarveStatus direction = directions[nextDirectionIndex];

			if (CanCarveInDirection(map, currentX, currentY, direction))
			{
				return direction;
			}

			directions.erase(directions.begin() + nextDirectionIndex);
		}

		return MazeCarveStatus::Restart;
	}

	void CarvePassages(Map& map, unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY)
	{
		unsigned int mazeRows = map.GetRowCount() - 2;
		unsigned int mazeColumns = map.GetColumnCount() - 2;

		// Fill entire maze area with walls
		for (unsigned int i = 0; i < mazeRows; i++)
		{
			for (unsigned int j = 0; j < mazeColumns; j++)
			{
				map.AddTile(i + 1, j + 1, MapTileType::Wall);
			}
		}

		// Start by opening space by the start and exit
		map.AddTile(startY, startX, MapTileType::None);
		map.AddTile(endY, endX, MapTileType::None);

		unsigned int currentX = startX;
		unsigned int currentY = startY;

		MazeCarveStatus status = MazeCarveStatus::Restart;
		while (status != MazeCarveStatus::Finish)
		{
			status = NextMazePosition(map, currentX, currentY, endX, endY);

			switch (status)
			{
			case MazeCarveStatus::Up:
				currentY -= 1;

				map.AddTile(currentY, currentX, MapTileType::None);

				break;
			case MazeCarveStatus::Down:
				currentY += 1;

				map.AddTile(currentY, currentX, MapTileType::None);

				break;
			case MazeCarveStatus::Left:
				currentX -= 1;

				map.AddTile(currentY, currentX, MapTileType::None);

				break;
			case MazeCarveStatus::Right:
				currentX += 1;

				map.AddTile(currentY, currentX, MapTileType::None);

				break;
			case MazeCarveStatus::Restart:
				currentX = startX;
				currentY = startY;

				break;

			default:
				break;
			}
		}
	}

	void PlacePlayer(Player& player, unsigned int row, unsigned int column)
	{
		float tileSize = (float)WALL_SIZE;

		float xOffset = tileSize / 2.0f;
		float yOffset = xOffset;

		glm::vec2 position((column * tileSize) + xOffset, (row * tileSize) + yOffset);
		player.SetPosition(position);
	}

	void GenerateMaze(Map& map, Player& player)
	{
		srand((unsigned int)time(NULL));

		// Place exit randomly on north border
		unsigned int exitColumn = (rand() % (map.GetColumnCount() - 2)) + 1;

		GenerateBorders(map, exitColumn);

		// Place start randomly on south border
		unsigned int startColumn = (rand() % (map.GetColumnCount() - 2)) + 1;
		unsigned int startRow = map.GetRowCount() - 2;

		// Maze algorithm
		CarvePassages(map, startColumn, startRow, exitColumn, 1);

		PlacePlayer(player, startRow, startColumn);

		map.Print();
	}
}
