#include "Settings.h"

#include "Window.h"

#include <assert.h>
#include <iostream>

namespace Labyrinth
{
	Window::Window()
	{
		m_Width = WINDOW_WIDTH;
		m_Height = WINDOW_HEIGHT;

		int windowFlags = 0;

		assert(SDL_Init(SDL_INIT_VIDEO) == 0);

		m_SDLWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, windowFlags);

		assert(m_SDLWindow != NULL);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_SDLWindow);
	}
}
