#pragma once

#include <Core.h>

namespace culling
{
	class MaskedSWOcclusionCulling;
}

namespace dooms
{
	namespace ui
	{
		namespace maskedOcclusionCulliingDebugger
		{
			extern void Render();

			extern void Initilize(culling::MaskedSWOcclusionCulling* const culling);
		}
	}
}
