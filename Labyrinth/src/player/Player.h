#pragma once

#include <glm/glm.hpp>

namespace Labyrinth
{
	class Player
	{
	public:
		Player(glm::vec2 position, float rotation);
		~Player();

		void Update();

		inline glm::vec2 GetPosition() { return m_Position; };
		inline void SetPosition(glm::vec2 position) { m_Position = position; };

		inline float GetAngle() { return m_Angle; };
		inline void SetAngle(float angle) { m_Angle = angle; };

	private:
		glm::vec2 m_Position;
		float m_Angle;

		float m_MovementSpeed;
		float m_RotateSpeed;
	};
}
