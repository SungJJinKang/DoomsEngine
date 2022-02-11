#pragma once

#include <vector>

#include <Core.h>
#include <Graphics/Graphics_Core.h>
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
			FLOAT64 LastTIme;
			D_PROPERTY()
			UINT64 FrameCount;
			D_PROPERTY()
			FLOAT64 FPS;

			D_PROPERTY()
			UINT64 PreviousFrameDrawCallCounter;

			D_PROPERTY()
			std::vector<RenderingDebuggerModule*> mRenderingDebuggerModule;

			void AppendDefaultRenderingDebuggerModules();
			void UpdateFPS();

		public :

			RenderingDebugger();

			void Initialize();
			void LateInitialize();
			void Update();

			void PreRender();
			void Render();
			void PostRender();

			FORCE_INLINE FLOAT64 GetFPS()
			{
				return FPS;
			}
		};
	}
}
