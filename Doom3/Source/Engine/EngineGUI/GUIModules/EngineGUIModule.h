#pragma once

#include <Core.h>

#include "EngineGUIModule.reflection.h"
namespace dooms
{
	namespace ui
	{
		class D_CLASS EngineGUIModule : public DObject
		{
			GENERATE_BODY()
		private:

		public:

			D_PROPERTY()
			bool mIsEnabled;

			EngineGUIModule();

			virtual void Init() = 0;
			virtual void Render() = 0;
		};
	}
}

