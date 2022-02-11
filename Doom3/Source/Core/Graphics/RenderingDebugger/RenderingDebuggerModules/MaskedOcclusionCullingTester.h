#pragma once

#include <Core.h>
#include "RenderingDebuggerModule.h"

#include "MaskedOcclusionCullingTester.reflection.h"
namespace culling
{
	class SWDepthBuffer;
}
namespace dooms
{
	namespace graphics
	{
		class D_CLASS MaskedOcclusionCullingTester : public RenderingDebuggerModule
		{
			//GENERATE_BODY()

		private:

			void DebugBinnedTriangles(const culling::SWDepthBuffer* const depthBuffer);
			void DebugTileCoverageMask(const culling::SWDepthBuffer* const depthBuffer);
			void DebugTileL0MaxDepthValue(const culling::SWDepthBuffer* const depthBuffer);

		public:

			void Initialize() override;
			void PreRender() override;
			void Render() override;
			void PostRender() override;

		};
	}
}

