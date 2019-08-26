#include "Settings.h"

#include "Player.h"

#include "application/Application.h"
#include "map/Map.h"
#include "ray_caster/RayCaster.h"

#include <SDL.h>

namespace Labyrinth
{
	Player::Player(glm::vec2 position, float rotation)
	{
		m_Position = position;
		m_Angle = rotation;

		m_MovementSpeed = 90.0f;
		m_RotateSpeed = 120.0f;
	}

	Player::~Player()
	{}

	void Player::Update()
	{
		float deltaTime = (float)Application::MainClock().GetDeltaTime();
		float toAngle = m_Angle;
		
		InputManager& inputManager = Application::MainInputManager();
		
		if (inputManager.KeyPressed((char)SDLK_LEFT))
		{
			toAngle -= m_RotateSpeed * deltaTime;
		}

		if (inputManager.KeyPressed((char)SDLK_RIGHT))
		{
			toAngle += m_RotateSpeed * deltaTime;
		}

		toAngle = fmod(toAngle, 360.0f);
		if (toAngle < 0)
		{
			toAngle += 360.0f;
		}

		glm::vec2 toPosition = m_Position;

		float walkDirection = 0.0f;

		if (inputManager.KeyPressed((char)SDLK_UP))
		{
			walkDirection += 1.0f;
		}

		if (inputManager.KeyPressed((char)SDLK_DOWN))
		{
			walkDirection -= 1.0f;
		}

		float angleRadians = glm::radians(toAngle);

		float movement = walkDirection * m_MovementSpeed * deltaTime;
		toPosition.x += glm::cos(angleRadians) * movement;
		toPosition.y += glm::sin(angleRadians) * movement;

		MapTileType tileType = Application::MainScene().GetMap().TileAtGridCoordinate(toPosition.x, toPosition.y);
		
		if (tileType == MapTileType::None)
		{
			m_Position = toPosition;
			m_Angle = toAngle;
		}
		else if (tileType == MapTileType::Exit)
		{
			Application::Get().Win();
		}
	}
}
