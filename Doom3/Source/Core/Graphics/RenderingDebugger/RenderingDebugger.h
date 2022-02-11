#pragma once

#include <vector>

#include <Core.h>
#include "../Graphics_Core.h"
#include <Simple_SingleTon/Singleton.h>

#include "RenderingDebugger.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class RenderingDebuggerModule;
		class DOOM_API D_CLASS RenderingDebugger : public DObject, public ISingleton<RenderingDebugger>
		{
			GENERATE_BODY()
			
		private:

			D_PROPERTY()
			std::vector<RenderingDebuggerModule*> mRenderingDebuggerModule;

			void AppendDefaultRenderingDebuggerModules();

		public :

			RenderingDebugger();

			void Initialize();
			void LateInitialize();
			void Update();

			void PreRender();
			void Render();
			void PostRender();
		};
	}
}
