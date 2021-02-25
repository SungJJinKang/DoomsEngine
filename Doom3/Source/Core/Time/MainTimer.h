#pragma once

#include "../Core.h"
namespace doom
{
	namespace time
	{
		class MainTimer
		{
			friend class Time_Server;
		private:

			static inline unsigned long long mLastTickCount{};

			/// <summary>
			/// https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
			/// </summary>
			static inline unsigned long long mCurrentTickCount{};
			static inline float mDeltaTime{};
			static inline unsigned long long mFixedDeltaTime{};

			static inline unsigned int mFrameCounter{ 0 };

			static void InitTimer();
			static void UpdateTimer();

		public:

			/// <summary>
			/// https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
			/// </summary>
			[[nodiscard]] static unsigned long long GetCurrentTime() noexcept
			{
				return MainTimer::mCurrentTickCount;
			}
			[[nodiscard]] static float GetDeltaTime() noexcept
			{
				return MainTimer::mDeltaTime ;
			}
			[[nodiscard]] static float GetFixedDeltaTime() noexcept
			{
				return MainTimer::mDeltaTime;
			}


			//If you want to get true value per n frame, use this function
			[[nodiscard]] static bool GetFrameStep(unsigned int step) noexcept
			{
				D_ASSERT(step != 0);
				return mFrameCounter % step == 0;
			}
		};
	}
}

using namespace doom::time;