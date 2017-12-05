#pragma once
#include <chrono>
#include "GLFW/glfw3.h"

#define SECONDS_TO_MILLI (1000.0)
#define SECONDS_TO_MICRO (1000.0 * 1000.0)
#define SECONDS_TO_NANO  (1000.0 * 1000.0 * 1000.0)

namespace doo
{
	typedef std::chrono::high_resolution_clock Clock;


	class TimeWrapper
	{
	public:
		friend class Game;

		TimeWrapper() = default;
		

		static double GetTimeSinceStart()
		{
			return glfwGetTime();
		}

		double GetFrameTimeMilliseconds() const
		{
			return getDiff() * SECONDS_TO_MILLI;
		}

		double GetFrameTimeNanoseconds() const
		{
			return getDiff() * SECONDS_TO_NANO;
		}

		double GetFrameTimeMicroseconds() const
		{
			return getDiff() * SECONDS_TO_MICRO;
		}

		double GetFrameTimeSeconds() const
		{
			return getDiff();
		}

		void Restart()
		{
			glfwSetTime(0);
		}


	private:

		double getDiff() const
		{
			return m_elapsedTime;
		}

		void startRecording()
		{
			m_timeSinceLastRecord = glfwGetTime();
		}

		void stopRecording()
		{
			m_elapsedTime = glfwGetTime() - m_timeSinceLastRecord;
		}

	private:
		double m_timeSinceLastRecord;
		double m_elapsedTime = 0;
	};
}
