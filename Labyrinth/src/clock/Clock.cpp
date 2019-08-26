#include "Settings.h"

#include "Clock.h"

#include <SDL.h>

namespace Labyrinth
{
	Clock* Clock::Create()
	{
		return new Clock();
	}

	Clock::Clock()
	{
		m_PreviousTime = 0;
		m_CurrentTime = 0;
		m_DeltaTime = 0;

		m_TotalTime = 0;

		m_TargetFrameRate = 1.0f / (float)FPS;
	}

	Clock::~Clock()
	{}

	void Clock::Update(double ticks)
	{
		m_PreviousTime = m_CurrentTime;
		m_CurrentTime = ticks;
		m_DeltaTime = m_CurrentTime - m_PreviousTime;

		m_TotalTime += m_DeltaTime;

		if (m_DeltaTime < m_TargetFrameRate)
		{
			SDL_Delay(((uint32_t)m_TargetFrameRate - (uint32_t)m_DeltaTime) * 1000);
		}
	}
}
