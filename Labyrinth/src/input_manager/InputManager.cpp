#include "InputManager.h"

#include "application/Application.h"

#include <SDL.h>

namespace Labyrinth
{
	InputManager::InputManager()
	{
		m_Keys = SDL_GetKeyboardState(NULL);
	}

	InputManager::~InputManager()
	{}

	void InputManager::Poll()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Application::Get().Stop();
				break;

			default:
				break;
			}

		default:
			break;
		}

		SDL_PumpEvents();
	}

	bool InputManager::KeyPressed(char key)
	{
		return m_Keys[key];
	}
}
