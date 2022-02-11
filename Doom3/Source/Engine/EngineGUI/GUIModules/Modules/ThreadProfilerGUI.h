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

			std::vector<UINT64> ThreadCycleInSecond{};
			std::vector<UINT64> ThreadCycleCounter1{};
			std::vector<UINT64> ThreadCycleCounter2{};
			float ElapsedTime{ 10000.0f };

			void UpdateThreadCycle();

		public:

			void Init() override;
			void Render() override;
		};
	}
}


