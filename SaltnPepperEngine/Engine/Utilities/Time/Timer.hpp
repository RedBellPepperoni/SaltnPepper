#ifndef TIMER_H
#define TIMER_H
#include "Core/EngineDefines.hpp"
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimeStamp;

namespace SaltnPepperEngine
{

	class SNP_API Timer
	{

	public:

		/// <summary>
		/// Returns the Current Time in Seconds (Uses std::chrono)
		/// </summary>
		static inline TimeStamp Now()
		{
			return std::chrono::high_resolution_clock::now();
		}
		
		/// <summary>
		/// Updates the cached time with the current time
		/// </summary>
		inline void UpdateTime()
		{
			m_cachedTime = Now();
		}

		/// <summary>
		///  Get the Delta Time and Update the chached time
		/// </summary>
		inline double CacheDelta()
		{
			TimeStamp timepoint = Now();
			double delta = GetDeltaSecondsSince(timepoint);
			m_cachedTime = timepoint;

			return delta;
		}

		/// <summary>
		/// Gets the time in seconds from the given time and the cached time
		/// </summary>
		inline double GetDeltaSecondsSince(std::chrono::high_resolution_clock::time_point timepoint) const
		{
			std::chrono::duration<double> span = std::chrono::duration_cast<std::chrono::duration<double>>(timepoint - m_cachedTime);
			return span.count();
		}

		/// <summary>
		/// Gets the time in seconds from the last cached and the current time
		/// </summary>
		inline double GetDeltaSeconds() const
		{
			return GetDeltaSecondsSince(Now());
		}

		/// <summary>
		/// Gets the Time Value in Milliseconds elapsed between the current time and cached time
		/// </summary>
		inline double GetDeltaMiliSeconds()
		{
			GetDeltaSeconds() * 1000.0; 
		}

		inline TimeStamp GetCached() const
		{
			return m_cachedTime;
		}

	protected:
	
		TimeStamp m_cachedTime;

	};

}




#endif // !TIMER_H

