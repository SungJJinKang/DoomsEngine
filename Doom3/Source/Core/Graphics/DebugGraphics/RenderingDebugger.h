#pragma once

#include <Core.h>
#include "../Graphics_Core.h"


#ifdef DEBUG_DRAWER

#include "OverDrawVisualization.h"

namespace doom
{
	namespace graphics
	{
		class RenderingDebugger
		{
		private:

			inline static unsigned long long DrawCallCounter = 0;
			inline static unsigned long long PreviousFrameDrawCallCounter = 0;

		public :

			inline static OverDrawVisualization mOverDrawVisualization{};

			FORCE_INLINE static void IncrementDrawCallCounter()
			{
				DrawCallCounter++;
			}

			FORCE_INLINE static void ResetDrawCallCounter()
			{
				PreviousFrameDrawCallCounter = DrawCallCounter;
				DrawCallCounter = 0;
			}

			FORCE_INLINE static unsigned long long GetDrawCallCounter()
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

#ifdef DEBUG_MODE

#ifndef INCREMENT_DRAWCALL_COUNTER
#define INCREMENT_DRAWCALL_COUNTER doom::graphics::RenderingDebugger::IncrementDrawCallCounter()
#endif

#ifndef RESET_DRAWCALL_COUNTER
#define RESET_DRAWCALL_COUNTER doom::graphics::RenderingDebugger::ResetDrawCallCounter()
#endif

#ifndef GET_DRAWCALL_COUNTER
#define GET_DRAWCALL_COUNTER doom::graphics::RenderingDebugger::GetDrawCallCounter()
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