#pragma once


#include "../Core.h"

#include <functional>

#include "RunnableThread.h"
#include <../Helper/Simple_SingleTon/Singleton.h>

#include "GameThread.reflection.h"
namespace dooms
{
	namespace thread
	{
		class DOOM_API D_CLASS GameThread : public RunnableThread, public ISingleton<GameThread>
		{
			GENERATE_BODY()

		public:

			const char* GetThreadName() const override;
			EThreadType GetThreadType() const override;

			virtual void InitFromCallerThread() override;
			bool IsAllowMultipleThreadOfThisThreadType() const override;

			void SetTickFunction(std::function<bool()> InTickFunction);

		protected:

			bool IsCreateNewThread() override;

			/**
			 * \brief this function will be called from GameEngineEntryPoint
			 */
			virtual void TickFromRunnableThread() override;
			EThreadPriority GetRecommendedPriorityOfThreadType() const override;

		private:
			
			std::function<bool()> TickFunction{};
			
		};
	}
}

