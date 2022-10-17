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

			D_PROPERTY()
			bool bmIsInitialized;

		public:

			D_PROPERTY()
			bool mIsEnabled;

			EngineGUIModule();

			virtual void Init();
			void InitIfNotInitialized();
			virtual void Render() = 0;
		};
	}
}

