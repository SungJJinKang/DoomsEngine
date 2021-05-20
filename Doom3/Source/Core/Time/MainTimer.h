#pragma once

#include "../Core.h"

#include <OS.h>

#include <API/OpenglAPI.h>

#include <UserInput_Server.h>
namespace doom
{
	class GameCore;
	namespace time
	{
		class MainTimer : public ISingleton<MainTimer>
		{
			friend class ::doom::GameCore;
			friend class Time_Server;

			struct TimeStep
			{
				double mLastTickCount{};
				double mCurrentTickCount{};
				float mDeltaTime{};
			};
		private:

			static inline TimeStep mFrameTime{};
			static inline TimeStep mFixedTime{};
			static inline float CurrentFrame{};
			
			static inline unsigned int mFrameCounter{ 0 };

			static void InitTimer();
			
			static void UpdateFrameTimer()
			{
				double currentTime = glfwGetTime();// OS::GetSingleton()->_GetTickCount();
				doom::time::MainTimer::mFrameTime.mCurrentTickCount = currentTime;

				doom::time::MainTimer::mFrameTime.mDeltaTime = static_cast<float>(currentTime - doom::time::MainTimer::mFrameTime.mLastTickCount);
				doom::time::MainTimer::mFrameTime.mLastTickCount = currentTime;

				MainTimer::CurrentFrame = static_cast<float>(1.0f / doom::time::MainTimer::mFrameTime.mDeltaTime);

				++mFrameCounter;
			}
			static void ResetFixedTimer()
			{
				doom::time::MainTimer::mFixedTime.mLastTickCount = glfwGetTime();
			}
			static void UpdateFixedTimer()
			{
				double currentTime = glfwGetTime();
				doom::time::MainTimer::mFixedTime.mCurrentTickCount = currentTime;

				doom::time::MainTimer::mFixedTime.mDeltaTime = static_cast<float>(currentTime - doom::time::MainTimer::mFixedTime.mLastTickCount);
				doom::time::MainTimer::mFixedTime.mLastTickCount = currentTime;

#ifdef DEBUG_MODE
				if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F5))
				{
					D_DEBUG_LOG({ "Current Frame : ", std::to_string(1.0 / doom::time::MainTimer::mFrameTime.mDeltaTime) });
				}
#endif
			}
			static void AdvanceAFrame()
			{

			}

		public:

			/// <summary>
			/// This value will be updated at every frame
			/// If you want to check whether frame pass without OnEndFrame, use this tickcount and compare last one
			/// https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
			/// </summary>
			[[nodiscard]] FORCE_INLINE static double GetCurrentTickCount() noexcept
			{
				return MainTimer::mFrameTime.mCurrentTickCount;
			}
			
			/// <summary>
			/// Frame Dependent Delta time
			///  Don't use at FixedUpdate, Use at Update
			/// </summary>
			[[nodiscard]] FORCE_INLINE static float GetDeltaTime() noexcept
			{
				return MainTimer::mFrameTime.mDeltaTime ;
			}

			/// <summary>
			/// Don't use at Update, Use at FixedUpdate
			/// </summary>
			[[nodiscard]] FORCE_INLINE static float GetFixedDeltaTime() noexcept
			{
				return MainTimer::mFixedTime.mDeltaTime;
			}

			[[nodiscard]] FORCE_INLINE static float GetCurrentFrame() noexcept
			{
				return MainTimer::CurrentFrame;
			}

			//If you want to get true value per n frame, use this function
			[[nodiscard]] FORCE_INLINE static bool GetFrameStep(unsigned int step) noexcept
			{
				D_ASSERT(step != 0);
				return mFrameCounter % step == 0;
			}

			
		};
	}
}

using namespace doom::time;