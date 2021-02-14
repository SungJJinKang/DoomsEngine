#pragma once

#include <chrono>
#include "../Core.h"
#include "../Game/IGameFlow.h"
#include "../Singleton.h"


namespace doom
{
	class GameCore;

	namespace time
	{
		class Time_Server : public IGameFlow, public ISingleton<Time_Server>
		{
			friend class ::doom::GameCore;

		private:

			std::chrono::high_resolution_clock::time_point mLastTime{};
			/// <summary>
			/// https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
			/// </summary>
			static inline long long mCurrentTime{};
			static inline double mDeltaTime{};
			static inline double mFixedDeltaTime{};

			static inline unsigned int mFrameCounter{ 0 };

			void Init() noexcept override;
			void Update() noexcept override;
			void OnEndOfFrame() noexcept override;

			

		public:

			/// <summary>
			/// https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
			/// </summary>
			[[nodiscard]] static long long GetCurrentTime() noexcept
			{
				return Time_Server::mCurrentTime;
			}
			[[nodiscard]] static double GetDeltaTime() noexcept
			{
				return Time_Server::mDeltaTime;
			}
			[[nodiscard]] static double GetFixedDeltaTime() noexcept
			{
				return Time_Server::mDeltaTime;
			}

			[[nodiscard]] static bool GetFrameStep(unsigned int step) noexcept
			{
				D_ASSERT(step != 0);
				return mFrameCounter % step == 0;
			}
		};
	}
	
}

using namespace doom::time;
