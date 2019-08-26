#include "Settings.h"

#include "Renderer.h"

#include "application/Application.h"

#include <assert.h>

namespace Labyrinth
{
	Renderer::Renderer(Window& window)
	{
		int rendererFlags = SDL_RENDERER_ACCELERATED;

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

		m_SDLRenderer = SDL_CreateRenderer(window.GetSDLWindow(), -1, rendererFlags);

		assert(SDL_CreateRenderer(window.GetSDLWindow(), -1, rendererFlags) == NULL);

		m_ColorBuffer = std::make_unique<ColorBuffer>();

		m_SDLColorTexture = SDL_CreateTexture(
			m_SDLRenderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING,
			(int)COLOR_BUFFER_WIDTH,
			(int)COLOR_BUFFER_HEIGHT
		);
	}

	Renderer::~Renderer()
	{
		SDL_DestroyRenderer(m_SDLRenderer);
	}

	void Renderer::PrepareRender()
	{
		m_ColorBuffer->ClearWithColor(FLOOR_COLOR);
	}

	void Renderer::Render()
	{
		SDL_UpdateTexture(
			m_SDLColorTexture,
			NULL,
			m_ColorBuffer->GetBuffer(),
			(int)((uint32_t)WINDOW_WIDTH * sizeof(uint32_t))
		);
		SDL_RenderCopy(m_SDLRenderer, m_SDLColorTexture, NULL, NULL);

		SDL_RenderPresent(m_SDLRenderer);
	}

	void Renderer::DrawRectangleColor(unsigned int x, unsigned int y, unsigned int height, uint32_t color)
	{
		m_ColorBuffer->DrawColorToBuffer(x, y, height, color);
	}

	void Renderer::DrawRectangleTexture(unsigned int x, unsigned int stripHeight, float wallTopPixel, float wallBottomPixel, float textureXOffset, MapTileType tileType, uint32_t shading)
	{
		m_ColorBuffer->DrawTextureToBuffer(x, stripHeight, wallTopPixel, wallBottomPixel, textureXOffset, tileType, shading);
	}
}
