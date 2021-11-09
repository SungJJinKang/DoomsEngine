#pragma once

#include "../Core.h"

#include <OS.h>

#include <UserInput_Server.h>
namespace dooms
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
		class DOOM_API D_CLASS MainTimer : public DObject, public ISingleton<MainTimer>
		{

			DOBJECT_CLASS_BODY(MainTimer);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

			friend class ::dooms::GameCore;
			friend class Time_Server;

			
		private:

			TimeStep mFrameTime{};
			TimeStep mFixedTime{};
			FLOAT32 CurrentFrame{};
			
			UINT64 mFrameCounterForStep{ 0 };

			void InitTimer();
			
			void UpdateFrameTimer();
			void ResetFixedTimer();
			void UpdateFixedTimer();
			void AdvanceAFrame()
			{

			}

		public:

			/// <summary>
			/// This value will be updated at every frame
			/// If you want to check whether frame pass without OnEndFrame, use this tickcount and compare last one
			/// https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
			/// </summary>
			NO_DISCARD FORCE_INLINE FLOAT64 GetCurrentTickCount() noexcept
			{
				return MainTimer::mFrameTime.mCurrentTickCount;
			}
			
			/// <summary>
			/// Frame Dependent Delta time
			///  Don't use at FixedUpdate, Use at Update
			/// </summary>
			NO_DISCARD FORCE_INLINE FLOAT32 GetDeltaTime() noexcept
			{
				return MainTimer::mFrameTime.mDeltaTime ;
			}

			/// <summary>
			/// Don't use at Update, Use at FixedUpdate
			/// </summary>
			NO_DISCARD FORCE_INLINE FLOAT32 GetFixedDeltaTime() noexcept
			{
				return MainTimer::mFixedTime.mDeltaTime;
			}

			NO_DISCARD FORCE_INLINE FLOAT32 GetCurrentFrame() noexcept
			{
				return MainTimer::CurrentFrame;
			}

			//If you want to get true value per n frame, use this function
			NO_DISCARD FORCE_INLINE bool GetFrameStep(UINT32 step) noexcept
			{
				D_ASSERT(step != 0);
				return MainTimer::mFrameCounterForStep % step == 0;
			}

			NO_DISCARD FORCE_INLINE UINT64 GetCurrentFrameCount() noexcept
			{
				return MainTimer::mFrameCounterForStep;
			}
			
		};
	}
}

using namespace dooms::time;