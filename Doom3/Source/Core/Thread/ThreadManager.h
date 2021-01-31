#pragma once

#include "Thread.h"
#include <array>

namespace doom
{
	namespace thread
	{

#define THREAD_COUNT 6
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
			static std::array<Thread, THREAD_COUNT> mManagedThreads; 
		public:
			
			static Thread& GetThread(size_t threadInded);
	

		};
	}
}


