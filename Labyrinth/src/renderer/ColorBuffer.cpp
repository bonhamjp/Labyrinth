#include "Settings.h"

#include "ColorBuffer.h"

#include "application/Application.h"

#include <algorithm>

namespace Labyrinth
{
	ColorBuffer::ColorBuffer()
	{
		m_Width = WINDOW_WIDTH;
		m_Height = WINDOW_HEIGHT;

		m_Buffer = (uint32_t*)malloc(sizeof(uint32_t) * m_Width * m_Height);
	}

	ColorBuffer::~ColorBuffer()
	{
		free(m_Buffer);
	}

	void ColorBuffer::ClearWithColor(uint32_t color)
	{
		for (unsigned int i = 0; i < (m_Width * m_Height); i++)
		{
			m_Buffer[i] = color;
		}
	}

	void ColorBuffer::DrawColorToBuffer(unsigned int x, unsigned int y, unsigned int height, uint32_t color)
	{
		for (unsigned int i = 0; i < height; i++)
		{
			m_Buffer[((y + i) * m_Width) + x] = color;
		}
	}

	void ColorBuffer::DrawTextureToBuffer(unsigned int x, unsigned int stripHeight, float wallTopPixel, float wallBottomPixel, float textureXOffset, MapTileType tileType, uint32_t shading)
	{
		float tileSize = (float)WALL_SIZE;

		textureXOffset = std::min(std::max(textureXOffset, 0.0f), tileSize);

		float startDistanceFromTop = (stripHeight / 2.0f) - ((float) COLOR_BUFFER_HEIGHT / 2.0f);
		float topOffset = tileSize / stripHeight;

		for (unsigned int i = ((unsigned int)wallTopPixel); i < ((unsigned int)wallBottomPixel); i++)
		{
			float distanceFromTop = i + startDistanceFromTop;
			int textureYOffset = std::min((int)floor(std::max(distanceFromTop * topOffset, 0.0f)), WALL_SIZE);

			uint32_t texel = Application::MainTextureManager().GetTexelAt(tileType, textureYOffset, (int) floor(textureXOffset));
			
			m_Buffer[(i * m_Width) + x] = texel + shading;
		}
	}

	uint32_t* ColorBuffer::GetBuffer()
	{
		return m_Buffer;
	}
}
