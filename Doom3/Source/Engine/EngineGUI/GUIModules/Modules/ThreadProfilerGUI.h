#pragma once

#include "../EngineGUIModule.h"

#include "ThreadProfilerGUI.reflection.h"
namespace dooms
{
	namespace ui
	{
		class D_CLASS ThreadProfilerGUI : public EngineGUIModule
		{
			GENERATE_BODY()

		private:

			struct FThreadCycleContainer
			{
				const char* ThreadName;
				UINT64 ThreadCycleInSecond{};
				UINT64 ThreadCycleCounter1{};
				UINT64 ThreadCycleCounter2{};
			};
			std::vector<FThreadCycleContainer> ThreadCycleContainerList{};

			float ElapsedTime{ 10000.0f };

			void UpdateThreadCycle();

		public:

			void Init() override;
			void Render() override;
		};
	}
}


