#pragma once

#include <array>
#include <thread>

#include "../../Helper/Singleton.h"
#include "../Game/IGameFlow.h"

#define THREAD_COUNT (5)

namespace doom
{
	namespace resource
	{
		class Thread;
		/// <summary>
		/// ThreadManager manage threads
		/// Never make thread without this ThreadManager class
		/// Thread count is limited to THREAD_COUNT
		/// 
		/// 
		/// Each Thread have a role
		/// So Use GetThread(index) function and Get thread reference and Pass Task!!!!
		/// </summary>
		class ThreadManager : public IGameFlow, public ISingleton<ThreadManager>
		{
		private:
			std::thread::id mMainThreadId{};
			Thread* mManagedSubThreads{ nullptr };
			bool bmIsInitialized{ false };

		protected:
			virtual void Init() final;
			virtual void Update() final;

		public:
			void InitializeThreads();
			void DestroyThreads();
			Thread& GetThread(size_t threadIndex);
	

		};
	}
}


