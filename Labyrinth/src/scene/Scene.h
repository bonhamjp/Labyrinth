#pragma once

#include "clock/Clock.h"
#include "map/Map.h"
#include "camera/Camera.h"
#include "player/Player.h"

#include <memory>

namespace Labyrinth
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		void Update();
		void Render();

		inline Map& GetMap() { return *m_Map; };

		double GetRunTime() { return m_Clock->GetTotalTime(); };

	protected:
		std::unique_ptr<Clock> m_Clock;
		std::unique_ptr<Map> m_Map;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Player> m_Player;

		void _SetMaze();
	};
}
