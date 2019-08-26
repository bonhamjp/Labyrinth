#pragma once

#include "ColorBuffer.h"

#include "window/Window.h"
#include "map/Map.h"

#include <memory>

#include <SDL.h>

namespace Labyrinth
{
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void PrepareRender();
		void Render();

		void DrawRectangleColor(unsigned int x, unsigned int y, unsigned int height, uint32_t color);
		void DrawRectangleTexture(unsigned int x, unsigned int stripHeight, float wallTopPixel, float wallBottomPixel, float textureXOffset, MapTileType tileType, uint32_t shading);

	private:
		SDL_Renderer* m_SDLRenderer;
		SDL_Texture* m_SDLColorTexture;

		std::unique_ptr<ColorBuffer> m_ColorBuffer;
	};
}

