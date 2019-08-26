#include "Settings.h"

#include "TextureManager.h"
#include "Textures.h"

namespace Labyrinth
{
	TextureManager::TextureManager()
	{
		m_Wall = MAIN_WALL_TEXTURE;
		m_Exit = EXIT_WALL_TEXTURE;
	}

	TextureManager::~TextureManager()
	{}

	uint32_t TextureManager::GetTexelAt(MapTileType tileType, unsigned int row, unsigned int column)
	{
		if (tileType == MapTileType::Wall)
		{
			return m_Wall[(row * WALL_SIZE) + column];
		}
		else if (tileType == MapTileType::Exit)
		{
			return m_Exit[(row * WALL_SIZE) + column];
		}

		return 0x000000FF;
	}
}
