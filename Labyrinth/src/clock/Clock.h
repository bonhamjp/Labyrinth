#pragma once

namespace Labyrinth
{
	class Clock
	{
	public:
		static Clock* Create();

		Clock();
		~Clock();

		void Update(double ticks);

		inline double GetDeltaTime() const { return m_DeltaTime; };
		inline double GetTotalTime() const { return m_TotalTime; };

	private:
		float m_TargetFrameRate;

		double m_CurrentTime;
		double m_PreviousTime;
		double m_DeltaTime;

		double m_TotalTime;
	};
}
