#pragma once

#include "map/Map.h"

#include <cstdint>

namespace Labyrinth
{
	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();

		uint32_t GetTexelAt(MapTileType tileType, unsigned int row, unsigned int column);

	private:
		uint32_t* m_Wall;
		uint32_t* m_Exit;
	};
}
