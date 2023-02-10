#pragma once

#include "../Core.h"

#include <vector>
#include <mutex>

#include "../Game/IGameFlow.h"
#include <../Helper/Simple_SingleTon/Singleton.h>
#include "EThreadType.h"

#include "ThreadManager.reflection.h"
namespace dooms
{
	namespace thread
	{
		class RunnableThread;

		class DOOM_API D_CLASS ThreadManager : public IGameFlow, public ISingleton<ThreadManager>
		{
			GENERATE_BODY()


		public:

			void Init(const int argc, char* const* const argv) override;
			void Update() override;
			void OnEndOfFrame() override;

			RunnableThread* CreateNewRunnableThread(const EThreadType TargetThreadType);
			std::vector<RunnableThread*> CreateNewRunnableThread(const EThreadType TargetThreadType, const INT32 Count);
			void TerminateRunnableThread(const EThreadType TargetThreadType, const INT32 Index, const bool bJoin);
			void TerminateAllRunnableThread(const bool bJoin);

			std::vector<RunnableThread*> GetRunnableThreadList() const;
			std::vector<RunnableThread*> GetRunnableThreadList(const EThreadType TargetThreadType) const;
			INT64 GetRunnableThreadCount() const;
			INT64 GetRunnableThreadCount(const EThreadType TargetThreadType) const;

			INT64 GetTotalRunnableThreadCount() const;

			INT32 GetCallerThreadIndexOfSameTypeThreads() const;

		protected:

			void OnSetPendingKill() override;

		private:

			D_PROPERTY()
			std::vector<RunnableThread*> RunnableThreadList{};

			mutable std::recursive_mutex RunnableThreadListMutex{};
		};
	}
}

