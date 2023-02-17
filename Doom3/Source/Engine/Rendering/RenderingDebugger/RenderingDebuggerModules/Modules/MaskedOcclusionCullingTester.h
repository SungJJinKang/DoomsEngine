#pragma once

#include <Core.h>
#include "../RenderingDebuggerModule.h"
#include <Collider/AABB.h>

#include "MaskedOcclusionCullingTester.reflection.h"
namespace culling
{
	class SWDepthBuffer;
	class OccluderListManager;
}
namespace dooms
{
	namespace graphics
	{
		class D_CLASS MaskedOcclusionCullingTester : public RenderingDebuggerModule
		{
			//GENERATE_BODY()

		private:

			std::vector<dooms::physics::AABB3D> CachedOccluderAABBList{};

			void DebugBinnedTriangles(const culling::SWDepthBuffer* const depthBuffer);
			void DebugTileCoverageMask(const culling::SWDepthBuffer* const depthBuffer);
			void DebugTileL0MaxDepthValue(const culling::SWDepthBuffer* const depthBuffer);
			void DebugOccluderBoundingBox(const culling::OccluderListManager* const OccluderListManager, const unsigned long long InTickCount);

		public:

			void Initialize() override;
			void PreRender() override;
			void Render(dooms::Camera* const targetCamera) override;
			void PostRender() override;
			const char* GetRenderingDebuggerModuleName() override;
		};
	}
}

