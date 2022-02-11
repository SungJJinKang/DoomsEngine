#pragma once

#include <Core.h>

#include "RenderingDebuggerModule.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class D_CLASS RenderingDebuggerModule : public DObject
		{
			GENERATE_BODY()

		private:

		public:

			D_PROPERTY()
			bool mIsEnabled;

			RenderingDebuggerModule();

			virtual void Initialize() = 0;
			virtual void PreRender() = 0;
			virtual void Render() = 0;
			virtual void LateRender();
			virtual void PostRender() = 0;
			virtual const char* GetRenderingDebuggerModuleName() = 0;
		};
	}
}

