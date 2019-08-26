#pragma once

#include "map/Map.h"

#include <cstdint>
#include <cstdlib>

namespace Labyrinth
{
	class ColorBuffer
	{
	public:
		ColorBuffer();
		~ColorBuffer();

		void ClearWithColor(uint32_t color);
		void DrawColorToBuffer(unsigned int x, unsigned int y, unsigned int height, uint32_t color);
		void DrawTextureToBuffer(unsigned int x, unsigned int stripHeight, float wallTopPixel, float wallBottomPixel, float textureXOffset, MapTileType tileType, uint32_t shading);

		uint32_t* GetBuffer();

	private:
		unsigned int m_Width;
		unsigned int m_Height;
		uint32_t* m_Buffer;
	};
}
