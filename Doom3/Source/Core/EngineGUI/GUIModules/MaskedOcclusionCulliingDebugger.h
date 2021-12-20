#pragma once

#include <Core.h>

namespace dooms
{
	namespace ui
	{
		namespace maskedOcclusionCulliingDebugger
		{
			extern void Render();

			extern void InitializeBinTriangle(const size_t rowCount, const size_t colCount);
			extern void SetBinnedTriangleCount(const size_t rowIndex, const size_t colIndex, const UINT32 triangleCount);
			extern void SetBinnedTriangleCount(const size_t tileIndex, const UINT32 triangleCount);
		}
	}
}
