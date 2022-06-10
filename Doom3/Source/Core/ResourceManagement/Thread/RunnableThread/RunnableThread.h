#pragma once

#include <Core.h>

#include <thread>
#include <memory>

#include "../eThreadType.h"
#include <OS/OS.h>

#include "RunnableThread.reflection.h"
namespace dooms
{
	namespace thread
	{
		class DOOM_API D_CLASS RunnableThread : public DObject
		{
			friend class ThreadManager;

			GENERATE_BODY()

		public:

			RunnableThread();

			virtual void Init_OnCallerThread();

			bool IsInitialized() const;
			bool IsTerminated() const;
			
			virtual const char* GetThreadName() const = 0;
			virtual eThreadType GetThreadType() const = 0;

			static RunnableThread* GetThreadLocalRunnableThread();
			static UINT64 GetThreadLocalRunnableThreadStackStartAddress();
			static bool IsOnThreadStack(const void* const address);

			HANDLE GetPlatformThreadHandler() const;
			bool IsValidPlatformThreadHandler();

			FORCE_INLINE UINT64 GetThreadCPUCycle() const
			{
				D_ASSERT(IsValidPlatformThreadHandler() == true);
				return dooms::os::_GetThreadCpuCycle(GetPlatformThreadHandler());
			}

			virtual bool IsAllowMultipleThreadOfThisThreadType() const = 0;
			HANDLE GetThreadHandle();
			bool IsExistThreadObject() const;

		protected:

			virtual void Init_OnRunnableThread();
			virtual void Tick_OnRunnableThread();
			virtual void OnTerminateRunnableThread_OnRunnableThread();
			virtual bool IsCreateNewThread();
			void SetThreadHandle(HANDLE Handle);
			
		private:

			std::atomic<bool> bIsInitialized = false;
			std::atomic<bool> bIsTerminated = false;
			volatile HANDLE PlatformThreadHandler = dooms::os::Get_PLATFORM_INVALID_HANDLE_CONSTANT();

			std::unique_ptr<std::thread> Thread{};
			
			inline static thread_local RunnableThread* ThreadLocalRunnableThread{ nullptr };
			inline static thread_local UINT64 ThreadLocalRunnableThreadStackStartAddress{ 0xFFFFFFFFFFFFFFFF };

			void Run_RunnableThread();
			
			void TerminateRunnableThread(const bool bJoin);
		};


		extern bool IsInGameThread();
		extern bool IsInRenderThread();
		extern eThreadType GetLocalThreadType();
	}
}

