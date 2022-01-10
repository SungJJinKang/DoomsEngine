#pragma once

#include <Core.h>
#include "../Graphics_Core.h"


#ifdef DEBUG_DRAWER

#include "RenderingDebugger.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class DOOM_API D_CLASS RenderingDebugger : public DObject
		{
			GENERATE_BODY()
			
		private:
			
			inline static FLOAT64 LastTIme = 0;
			inline static UINT64 FrameCount = 0;
			inline static FLOAT64 FPS = 0.0;
			
			inline static UINT64 PreviousFrameDrawCallCounter = 0;

			static void UpdateFPS();

		public :

			static void Update();

			FORCE_INLINE static FLOAT64 GetFPS()
			{
				return FPS;
			}
			
			static void PrintDrawCallCounter();
			static void UpdateInputForPrintDrawCallCounter();
			static void DrawRenderingBoundingBox();
		};
	}
}

#endif
