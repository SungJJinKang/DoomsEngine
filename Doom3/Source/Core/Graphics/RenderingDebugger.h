#pragma once

#include <Core.h>

namespace doom
{
	namespace graphics
	{
		class RenderingDebugger
		{
		private:

			inline static unsigned long long DrawCallCounter = 0;

		

		public :

			

		

			FORCE_INLINE static void IncrementDrawCallCounter()
			{
				DrawCallCounter++;
			}

			FORCE_INLINE static void ResetDrawCallCounter()
			{
				DrawCallCounter = 0;
			}

			FORCE_INLINE static unsigned long long GetDrawCallCounter()
			{
				return DrawCallCounter;
			}

			void PrintDrawCallCounter();
			void UpdateInputForPrintDrawCallCounter();
			void DrawRenderingBoundingBox();
		};
	}
}

