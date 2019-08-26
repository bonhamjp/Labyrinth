#include "Settings.h"

#include "Map.h"

#include <memory>
#include <string>
#include <iostream>

namespace Labyrinth
{
	Map::Map()
	{
		m_ColumnCount = MAP_COLUMNS;
		m_RowCount = MAP_ROWS;

		m_Width = m_ColumnCount * WALL_SIZE;
		m_Height = m_RowCount * WALL_SIZE;

		m_Tiles = (MapTileType*)malloc(m_ColumnCount * m_RowCount * sizeof(MapTileType));

		for (unsigned int i = 0; i < m_ColumnCount * m_RowCount; i++)
		{
			m_Tiles[i] = MapTileType::None;
		}
	}

	Map::~Map()
	{
		free(m_Tiles);
	}

	void Map::AddTile(unsigned int row, unsigned int column, MapTileType type)
	{
		m_Tiles[((m_ColumnCount * row) + column)] = type;
	}

	void Map::RemoveTile(unsigned int row, unsigned int column)
	{
		m_Tiles[((m_ColumnCount * row) + column)] = MapTileType::None;
	}

	MapTileType Map::TileAtGridCoordinate(float xPosition, float yPosition)
	{
		unsigned int row = (unsigned int)floor(yPosition / ((float)WALL_SIZE));
		unsigned int column = (unsigned int)floor(xPosition / ((float)WALL_SIZE));

		return m_Tiles[((m_ColumnCount * row) + column)];
	}

	MapTileType Map::TileAtGridIndices(unsigned int column, unsigned int row)
	{
		return m_Tiles[((m_ColumnCount * row) + column)];
	}

	void Map::Print()
	{
		for (unsigned int i = 0; i < m_RowCount; i++)
		{
			std::string row;

			for (unsigned int j = 0; j < m_ColumnCount; j++)
			{
				if (m_Tiles[((m_ColumnCount * i) + j)] == MapTileType::Wall)
				{
					row.append("x");
				}
				else
				{
					row.append(".");
				}
			}

			std::cout << row << std::endl;;
		}
	}
}
