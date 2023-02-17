#pragma once

#include <vector>

#include <Core.h>
#include <Graphics/Graphics_Core.h>
#include <SingleTon/Singleton.h>

#include "RenderingDebugger.reflection.h"
namespace dooms
{
	class Camera;
	namespace graphics
	{
		class RenderingDebuggerModule;
		class DebugDrawer;
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

			D_PROPERTY()
			DebugDrawer* DebugDrawerModule;

			void AppendDefaultRenderingDebuggerModules();
			void UpdateFPS();

		public :

			RenderingDebugger();

			void Initialize();
			void LateInitialize();
			void Update();

			void PreRender();
			void CameraRender(dooms::Camera* const targetCamera);
			void PostRender();

			FORCE_INLINE FLOAT64 GetFPS()
			{
				return FPS;
			}
		};
	}
}
