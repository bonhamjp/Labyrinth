#include "Settings.h"

#include "Camera.h"

#include "application/Application.h"
#include "scene/Scene.h"
#include "ray_caster/RayCaster.h"

#include <glm/glm.hpp>

#include <algorithm>

namespace Labyrinth
{
	Camera::Camera()
	{
		m_FieldOfView = FIELD_OF_VIEW;

		m_DegreeStep = m_FieldOfView / (float)COLOR_BUFFER_WIDTH;

		float halfProjectionWidth = ((float)COLOR_BUFFER_WIDTH) / 2.0f;
		float halfFOV = m_FieldOfView / 2.0f;

		m_DistanceToProjection = halfProjectionWidth / glm::tan(glm::radians(halfFOV));
	}

	Camera::~Camera()
	{}

	void Camera::Render(glm::vec2 position, float angle)
	{
		float currentAngle = angle - (m_FieldOfView / 2.0f);

		Renderer& renderer = Application::MainRenderer();
		
		for (unsigned int i = 0; i < COLOR_BUFFER_WIDTH; i++)
		{
			Ray currentRay = RayCaster::Cast(position, currentAngle);

			// Correct fishbowl effect
			float correctedDistance = currentRay.Distance * glm::cos(glm::radians(currentAngle - angle));

			// Full height of projected wall
			float stripHeight = ((float)WALL_SIZE / correctedDistance) * m_DistanceToProjection;

			// Distance from top and bottom of screen
			float wallTopPixel = std::max(((float)COLOR_BUFFER_HEIGHT / 2.0f) - (stripHeight / 2.0f), 0.0f);
			float wallBottomPixel = std::min(((float)COLOR_BUFFER_HEIGHT / 2.0f) + (stripHeight / 2.0f), (float)COLOR_BUFFER_HEIGHT);

			unsigned int shade = 0x00000000;
			if (currentRay.Type == RayCollisionType::Left || currentRay.Type == RayCollisionType::Right)
			{
				shade = -0x22222200;
			}

			// Draw sky first
			renderer.DrawRectangleColor(
				i,
				0,
				(unsigned int)wallTopPixel,
				SKY_COLOR
			);

			// Draw wall last
			renderer.DrawRectangleTexture(
				i,
				(unsigned int)stripHeight,
				wallTopPixel,
				wallBottomPixel,
				currentRay.TextureXOffset,
				currentRay.WallType,
				shade
			);

			currentAngle += m_DegreeStep;
		}
	}
}
