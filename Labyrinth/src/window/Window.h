#pragma once

#include <SDL.h>

namespace Labyrinth
{
	class Window
	{
	public:
		Window();
		~Window();

		inline unsigned int GetHeight() { return m_Height; };
		inline unsigned int GetWidth() { return m_Width; };

		inline SDL_Window* GetSDLWindow() { return m_SDLWindow; };

	private:
		unsigned int m_Width;
		unsigned int m_Height;

		SDL_Window* m_SDLWindow;
	};
}
