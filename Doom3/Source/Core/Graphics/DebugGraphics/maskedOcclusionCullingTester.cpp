#include "maskedOcclusionCullingTester.h"

#include "imgui.h"
#include <EngineGUI/PrintText.h>
#include <Graphics/DebugGraphics/DebugDrawer.h>

#define DEBUGGER_TILE_BOX_PADIDNG 0.002f

void dooms::graphics::maskedOcclusionCullingTester::DebugTileCoverageMask
(
	const culling::SWDepthBuffer* const depthBuffer
)
{
	std::atomic_thread_fence(std::memory_order_acquire);

	const float xScale = 2.0f / (float)(depthBuffer->mResolution.mColumnCount);
	const float yScale = 2.0f / (float)(depthBuffer->mResolution.mRowCount);

    for(size_t y = 0 ; y < depthBuffer->mResolution.mRowCount ; y++)
    {
		// y = 0 -> bottom
		for (size_t x = 0; x < depthBuffer->mResolution.mColumnCount; x++)
		{
			const culling::Tile* const tile = depthBuffer->GetTile(y, x);

			//draw -1 ~ 1
			dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DBox
			(
				math::Vector3(DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * x, DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * y, 0.0f),
				math::Vector3(-DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * (x + 1), -DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * (y + 1), 0.0f),
				(_mm256_testc_si256(tile->mHizDatas.l1CoverageMask, _mm256_set1_epi64x(0xFFFFFFFFFFFFFFFF)) == 1) ? eColor::Red : eColor::White
			);
		}
    }
	
}

void dooms::graphics::maskedOcclusionCullingTester::DebugBinnedTriangles
(
	const culling::SWDepthBuffer* const depthBuffer
)
{
	std::atomic_thread_fence(std::memory_order_acquire);

	const float xScale = 2.0f / (float)(depthBuffer->mResolution.mColumnCount);
	const float yScale = 2.0f / (float)(depthBuffer->mResolution.mRowCount);

	for (size_t y = 0; y < depthBuffer->mResolution.mRowCount; y++)
	{
		// y = 0 -> bottom
		for (size_t x = 0; x < depthBuffer->mResolution.mColumnCount; x++)
		{
			const culling::Tile* const tile = depthBuffer->GetTile(y, x);

			//draw -1 ~ 1
			dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DBox
			(
				math::Vector3(DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * x, DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * y, 0.0f),
				math::Vector3(-DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * (x + 1), -DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * (y + 1), 0.0f),
				depthBuffer->GetTile(y, x)->mBinnedTriangles.mCurrentTriangleCount > 0 ? eColor::Red : eColor::White
			);
		}
	}

}
