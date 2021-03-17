#pragma once

#include "../Core.h"

namespace doom
{
	namespace time
	{
		class MainTimer : public ISingleton<MainTimer>
		{
			friend class Time_Server;

			struct TimeStep
			{
				unsigned long long mLastTickCount{};
				unsigned long long mCurrentTickCount{};
				float mDeltaTime{};
			};
		private:

			static inline TimeStep mFrameTime{};
			static inline TimeStep mFixedTime{};
			static inline float CurrentFrame{};


			static inline unsigned int mFrameCounter{ 0 };

			static void InitTimer();
			

		public:

			/// <summary>
			/// This value will be updated at every frame
			/// If you want to check whether frame pass without OnEndFrame, use this tickcount and compare last one
			/// https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
			/// </summary>
			[[nodiscard]] static unsigned long long GetCurrentTickCount() noexcept
			{
				return MainTimer::mFrameTime.mCurrentTickCount;
			}
			
			/// <summary>
			/// Frame Dependent Delta time
			///  Don't use at FixedUpdate, Use at Update
			/// </summary>
			[[nodiscard]] static float GetDeltaTime() noexcept
			{
				return MainTimer::mFrameTime.mDeltaTime ;
			}

			/// <summary>
			/// Don't use at Update, Use at FixedUpdate
			/// </summary>
			[[nodiscard]] static float GetFixedDeltaTime() noexcept
			{
				return MainTimer::mFixedTime.mDeltaTime;
			}

			[[nodiscard]] static float GetCurrentFrame() noexcept
			{
				return MainTimer::CurrentFrame;
			}

			//If you want to get true value per n frame, use this function
			[[nodiscard]] static bool GetFrameStep(unsigned int step) noexcept
			{
				D_ASSERT(step != 0);
				return mFrameCounter % step == 0;
			}

			static void UpdateFrameTimer();
			static void ResetFixedTimer();
			static void UpdateFixedTimer();
			static void AdvanceAFrame();
		};
	}
}

using namespace doom::time;