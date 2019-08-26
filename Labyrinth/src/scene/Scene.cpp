#include "Settings.h"

#include "Scene.h"

#include "application/Application.h"
#include "map/Map.h"
#include "map/MazeGenerator.h"
#include "player/Player.h"

#include <glm/glm.hpp>

namespace Labyrinth
{
	Scene::Scene()
	{
		m_Map = std::make_unique<Map>();
		m_Camera = std::make_unique<Camera>();
		m_Player = std::make_unique<Player>(glm::vec2(0.0f, 0.f), 270.0f);

		_SetMaze();

		// Start clock after setup
		m_Clock = std::make_unique <Clock>();
	}

	Scene::~Scene()
	{
		m_Map.reset();
		m_Camera.reset();
		m_Player.reset();
		m_Clock.reset();
	}

	void Scene::Update()
	{
		m_Clock->Update(SDL_GetTicks() / 1000.0f);

		m_Player->Update();
	}

	void Scene::Render()
	{
		m_Camera->Render(m_Player->GetPosition(), m_Player->GetAngle());
	}

	void Scene::_SetMaze()
	{
		GenerateMaze(*m_Map, *m_Player);
	}
}
