#pragma once

#include "../Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/SWDepthBuffer.h"

namespace dooms
{
	namespace graphics
	{
		namespace maskedOcclusionCullingTester
		{
			void DebugBinnedTriangles(const culling::SWDepthBuffer* const depthBuffer);
			void DebugTileCoverageMask(const culling::SWDepthBuffer* const depthBuffer);
			void DebugTileL0MaxDepthValue(const culling::SWDepthBuffer* const depthBuffer);
		};
	}
}

