#pragma once

#include <array>
#include <thread>

namespace doom
{
	namespace thread
	{

#define THREAD_COUNT 5

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
		class ThreadManager
		{
		private:
			static inline std::thread::id mMainThreadId{};
			static inline Thread* mManagedSubThreads{ nullptr };
			static inline bool bmIsInitialized{ false };
		public:
			static void InitializeThreads();
			static void DestroyThreads();
			static Thread& GetThread(size_t threadIndex);
	

		};
	}
}


