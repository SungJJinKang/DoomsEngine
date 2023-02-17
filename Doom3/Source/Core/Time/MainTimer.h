#pragma once

#include "../Core.h"

#include <SingleTon/Singleton.h>

#include "MainTimer.reflection.h"
namespace dooms
{
	struct TimeStep
	{
		FLOAT64 mLastTickCount{};
		FLOAT64 mCurrentTickCount{};
		FLOAT64 mDeltaTime{};
	};

	class GameCore;
	namespace time
	{
		class DOOM_API D_CLASS MainTimer : public DObject, public ISingleton<MainTimer>
		{
			GENERATE_BODY()
			
			

			friend class ::dooms::GameCore;
			friend class Time_Server;

			
		private:

			TimeStep mFrameTime{};
			TimeStep mFixedTime{};
			FLOAT64 CurrentFrame{};
			
			UINT64 mFrameCounterForStep{ 0 };

			void InitTimer();

			/**
			 * \brief 
			 * \return return current time in seconds
			 */
			FLOAT64 GetTime() const;
			void UpdateFrameTimer();
			void ResetFixedTimer();
			void UpdateFixedTimer();
			void AdvanceAFrame()
			{

			}

		public:


			NO_DISCARD FORCE_INLINE FLOAT64 GetCurrentTime() noexcept
			{
				return MainTimer::mFrameTime.mCurrentTickCount;
			}
			
			/// <summary>
			/// Frame Dependent Delta time
			///  Don't use at FixedUpdate, Use at Update
			/// </summary>
			NO_DISCARD FORCE_INLINE FLOAT64 GetDeltaTime() noexcept
			{
				return MainTimer::mFrameTime.mDeltaTime ;
			}

			/// <summary>
			/// Don't use at Update, Use at FixedUpdate
			/// </summary>
			NO_DISCARD FORCE_INLINE FLOAT64 GetFixedDeltaTime() noexcept
			{
				return MainTimer::mFixedTime.mDeltaTime;
			}

			NO_DISCARD FORCE_INLINE FLOAT64 GetCurrentFrame() noexcept
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