#pragma once

#include "../EngineGUIModule.h"

#include "DrawCallCounterGUI.reflection.h"
namespace dooms
{
	namespace ui
	{
		class D_CLASS DrawCallCounterGUI : public EngineGUIModule
		{
			GENERATE_BODY()

		public:

			void Init() override;
			void Render() override;

		};
	}
}


