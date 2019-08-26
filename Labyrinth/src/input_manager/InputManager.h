#pragma once

#include <SDL.h>

namespace Labyrinth
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void Poll();

		bool KeyPressed(char key);

	private:
		const Uint8* m_Keys;
	};
}
