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

			inline static UINT64 DrawCallCounter = 0;
			inline static UINT64 PreviousFrameDrawCallCounter = 0;

		public :
			
			FORCE_INLINE static void IncrementDrawCallCounter()
			{
				DrawCallCounter++;
			}

			FORCE_INLINE static void ResetDrawCallCounter()
			{
				PreviousFrameDrawCallCounter = DrawCallCounter;
				DrawCallCounter = 0;
			}

			FORCE_INLINE static UINT64 GetDrawCallCounter()
			{
				return DrawCallCounter;
			}

			static void PrintDrawCallCounter();
			static void UpdateInputForPrintDrawCallCounter();
			static void DrawRenderingBoundingBox();
		};
	}
}

#endif

#if defined(DEBUG_MODE) || true

#ifndef INCREMENT_DRAWCALL_COUNTER
#define INCREMENT_DRAWCALL_COUNTER dooms::graphics::RenderingDebugger::IncrementDrawCallCounter()
#endif

#ifndef RESET_DRAWCALL_COUNTER
#define RESET_DRAWCALL_COUNTER dooms::graphics::RenderingDebugger::ResetDrawCallCounter()
#endif

#ifndef GET_DRAWCALL_COUNTER
#define GET_DRAWCALL_COUNTER dooms::graphics::RenderingDebugger::GetDrawCallCounter()
#endif

#else

#ifndef INCREMENT_DRAWCALL_COUNTER
#define INCREMENT_DRAWCALL_COUNTER
#endif

#ifndef RESET_DRAWCALL_COUNTER
#define RESET_DRAWCALL_COUNTER
#endif

#ifndef GET_DRAWCALL_COUNTER
#define GET_DRAWCALL_COUNTER
#endif

#endif