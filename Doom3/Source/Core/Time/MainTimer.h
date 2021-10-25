#pragma once

#include "../Core.h"

#include <OS.h>

#include <UserInput_Server.h>
namespace doom
{
	struct TimeStep
	{
		FLOAT64 mLastTickCount{};
		FLOAT64 mCurrentTickCount{};
		FLOAT32 mDeltaTime{};
	};

	class GameCore;
	namespace time
	{
		class MainTimer : public DObject, public ISingleton<MainTimer>
		{

			DOBJECT_CLASS_BODY(MainTimer);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

			friend class ::doom::GameCore;
			friend class Time_Server;

			
		private:

			static inline TimeStep mFrameTime{};
			static inline TimeStep mFixedTime{};
			static inline FLOAT32 CurrentFrame{};
			
			static inline UINT64 mFrameCounterForStep{ 0 };

			static void InitTimer();
			
			static void UpdateFrameTimer();
			static void ResetFixedTimer();
			static void UpdateFixedTimer();
			static void AdvanceAFrame()
			{

			}

		public:

			/// <summary>
			/// This value will be updated at every frame
			/// If you want to check whether frame pass without OnEndFrame, use this tickcount and compare last one
			/// https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
			/// </summary>
			[[nodiscard]] FORCE_INLINE static FLOAT64 GetCurrentTickCount() noexcept
			{
				return MainTimer::mFrameTime.mCurrentTickCount;
			}
			
			/// <summary>
			/// Frame Dependent Delta time
			///  Don't use at FixedUpdate, Use at Update
			/// </summary>
			[[nodiscard]] FORCE_INLINE static FLOAT32 GetDeltaTime() noexcept
			{
				return MainTimer::mFrameTime.mDeltaTime ;
			}

			/// <summary>
			/// Don't use at Update, Use at FixedUpdate
			/// </summary>
			[[nodiscard]] FORCE_INLINE static FLOAT32 GetFixedDeltaTime() noexcept
			{
				return MainTimer::mFixedTime.mDeltaTime;
			}

			[[nodiscard]] FORCE_INLINE static FLOAT32 GetCurrentFrame() noexcept
			{
				return MainTimer::CurrentFrame;
			}

			//If you want to get true value per n frame, use this function
			[[nodiscard]] FORCE_INLINE static bool GetFrameStep(UINT32 step) noexcept
			{
				D_ASSERT(step != 0);
				return MainTimer::mFrameCounterForStep % step == 0;
			}

			[[nodiscard]] FORCE_INLINE static UINT64 GetCurrentFrameCount() noexcept
			{
				return MainTimer::mFrameCounterForStep;
			}
			
		};
	}
}

using namespace doom::time;