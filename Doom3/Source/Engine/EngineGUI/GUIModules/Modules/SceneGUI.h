#pragma once

#include "../EngineGUIModule.h"

#include "SceneGUI.reflection.h"
namespace dooms
{
	namespace ui
	{
		class D_CLASS SceneGUI : public EngineGUIModule
		{
			GENERATE_BODY()

		private:

			size_t currentEntityIndex;

		public:

			void Init() override;
			void Render() override;

		};
	}
}
