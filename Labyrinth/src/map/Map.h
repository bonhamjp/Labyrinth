#pragma once

namespace Labyrinth
{
	enum class MapTileType
	{
		None = 0, Wall, Exit
	};

	class Map
	{
	public:
		Map();
		~Map();

		inline unsigned int GetColumnCount() { return m_ColumnCount; };
		inline unsigned int GetRowCount() { return m_RowCount; };

		inline unsigned int GetWidth() { return m_Width; };
		inline unsigned int GetHeight() { return m_Height; };

		void AddTile(unsigned int row, unsigned int column, MapTileType type);
		void RemoveTile(unsigned int row, unsigned int column);

		MapTileType TileAtGridCoordinate(float xPosition, float yPosition);
		MapTileType TileAtGridIndices(unsigned int column, unsigned int row);

		void Print();

	private:
		unsigned int m_ColumnCount;
		unsigned int m_RowCount;
		unsigned int m_Width;
		unsigned int m_Height;

		MapTileType* m_Tiles;
	};
}
