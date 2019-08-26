#pragma once

#include <glm/glm.hpp>

namespace Labyrinth
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Render(glm::vec2 position, float angle);

		inline float GetFieldOfView() { return m_FieldOfView; };
		inline float GetDegreeStep() { return m_DegreeStep; };
		inline float GetDistanceToProjection() { return m_DistanceToProjection; };

	protected:
		float m_FieldOfView;
		float m_DegreeStep;
		float m_DistanceToProjection;
	};
}
