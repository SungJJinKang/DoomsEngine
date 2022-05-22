#pragma once

#include "../Core.h"

#include <vector>
#include <memory>

#include "../Game/IGameFlow.h"
#include <../Helper/Simple_SingleTon/Singleton.h>
#include "eThreadType.h"

#include "ThreadManager.reflection.h"
namespace dooms
{
	namespace thread
	{
		class RunnableThread;

		class DOOM_API D_CLASS ThreadManager : public IGameFlow, public ISingleton<ThreadManager>
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			std::vector<RunnableThread*> RunnableThreadList;

		public:

			RunnableThread* CreateNewRunnableThread(const eThreadType TargetThreadType, const char* const BeautifulThreadName);

			std::vector<RunnableThread*> GetRunnableThread(const eThreadType TargetThreadType);
			std::vector<const RunnableThread*> GetRunnableThread(const eThreadType TargetThreadType) const;
			RunnableThread* GetRunnableThread(const char* const ThreadName);
			const RunnableThread* GetRunnableThread(const char* const ThreadName) const;

		};
	}
}

