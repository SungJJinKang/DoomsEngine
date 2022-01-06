#include "maskedOcclusionCullingTester.h"

#include "imgui.h"
#include <EngineGUI/PrintText.h>
#include <Graphics/DebugGraphics/DebugDrawer.h>
#include <Graphics/Graphics_Setting.h>
#include <Rendering/Camera.h>

#define DEBUGGER_TILE_BOX_PADIDNG_X 0.002f
#define DEBUGGER_TILE_BOX_PADIDNG_Y 0.002f

void dooms::graphics::maskedOcclusionCullingTester::DebugTileCoverageMask
(
	const culling::SWDepthBuffer* const depthBuffer
)
{
	std::atomic_thread_fence(std::memory_order_acquire);

	const float xScale = 2.0f / (float)(depthBuffer->mResolution.mColumnSubTileCount);
	const float yScale = 2.0f / (float)(depthBuffer->mResolution.mRowSubTileCount);

	const UINT32 screenWidth = depthBuffer->mResolution.mWidth;
	const UINT32 screenHeight = depthBuffer->mResolution.mHeight;

	//const UINT32 space = ((float)screenWidth / (float)screenHeight) * ((float)GetRowSubTileCount() / (float)GetColumnSubTileCount());

	for (INT32 subTileRowIndex = depthBuffer->mResolution.mRowSubTileCount - 1; subTileRowIndex >= 0; subTileRowIndex--)
	{
		for (INT32 subTileColIndex = 0; subTileColIndex < depthBuffer->mResolution.mColumnSubTileCount; subTileColIndex++)
		{
			const INT32 tileRowIndex = subTileRowIndex / (TILE_HEIGHT / SUB_TILE_HEIGHT);
			const INT32 tileColIndex = subTileColIndex / (TILE_WIDTH / SUB_TILE_WIDTH);

			const INT32 subTileRowIndexInTile = subTileRowIndex % (TILE_HEIGHT / SUB_TILE_HEIGHT);
			const INT32 subTileColIndexInTile = subTileColIndex % (TILE_WIDTH / SUB_TILE_WIDTH);

			D_ASSERT(subTileRowIndexInTile >= 0 && subTileRowIndexInTile < (TILE_HEIGHT / SUB_TILE_HEIGHT));
			D_ASSERT(subTileColIndexInTile >= 0 && subTileRowIndexInTile < (TILE_WIDTH / SUB_TILE_WIDTH));

			const culling::M256I L1CoverageMask = depthBuffer->GetTile(tileRowIndex, tileColIndex)->mHizDatas.L1CoverageMask;
			const INT32 subTileIndex = subTileColIndexInTile + subTileRowIndexInTile * (TILE_WIDTH / SUB_TILE_WIDTH);
			D_ASSERT(subTileIndex >= 0 && subTileIndex < 8);

			const int coverageMaskValue = reinterpret_cast<const int*>(&L1CoverageMask)[subTileIndex];

			dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DBox
			(
				math::Vector3(DEBUGGER_TILE_BOX_PADIDNG_X + -1.0f + xScale * subTileColIndex, DEBUGGER_TILE_BOX_PADIDNG_Y + -1.0f + yScale * subTileRowIndex, 0.0f),
				math::Vector3(-DEBUGGER_TILE_BOX_PADIDNG_X + -1.0f + xScale * (subTileColIndex + 1), -DEBUGGER_TILE_BOX_PADIDNG_Y + -1.0f + yScale * (subTileRowIndex + 1), 0.0f),
				(coverageMaskValue == (int)0xFFFFFFFF) ? eColor::Red : eColor::White
			);
		}
	}
	
}

void dooms::graphics::maskedOcclusionCullingTester::DebugTileL0MaxDepthValue
(
	const culling::SWDepthBuffer* const depthBuffer
)
{
	std::atomic_thread_fence(std::memory_order_acquire);

	const float xScale = 2.0f / (float)(depthBuffer->mResolution.mColumnSubTileCount);
	const float yScale = 2.0f / (float)(depthBuffer->mResolution.mRowSubTileCount);

	const UINT32 screenWidth = depthBuffer->mResolution.mWidth;
	const UINT32 screenHeight = depthBuffer->mResolution.mHeight;

	//const UINT32 space = ((float)screenWidth / (float)screenHeight) * ((float)GetRowSubTileCount() / (float)GetColumnSubTileCount());

	for (INT32 subTileRowIndex = depthBuffer->mResolution.mRowSubTileCount - 1; subTileRowIndex >= 0; subTileRowIndex--)
	{
		for (INT32 subTileColIndex = 0; subTileColIndex < depthBuffer->mResolution.mColumnSubTileCount ; subTileColIndex++)
		{
			const INT32 tileRowIndex = subTileRowIndex / (TILE_HEIGHT / SUB_TILE_HEIGHT);
			const INT32 tileColIndex = subTileColIndex / (TILE_WIDTH / SUB_TILE_WIDTH);

			const INT32 subTileRowIndexInTile = subTileRowIndex % (TILE_HEIGHT / SUB_TILE_HEIGHT);
			const INT32 subTileColIndexInTile = subTileColIndex % (TILE_WIDTH / SUB_TILE_WIDTH);

			D_ASSERT(subTileRowIndexInTile >= 0 && subTileRowIndexInTile < (TILE_HEIGHT / SUB_TILE_HEIGHT));
			D_ASSERT(subTileColIndexInTile >= 0 && subTileRowIndexInTile < (TILE_WIDTH / SUB_TILE_WIDTH));

			const culling::M256F L0MaxDepthValue = depthBuffer->GetTile(tileRowIndex, tileColIndex)->mHizDatas.L0SubTileMaxDepthValue;
			const INT32 subTileIndex = subTileColIndexInTile + subTileRowIndexInTile * (TILE_WIDTH / SUB_TILE_WIDTH);
			D_ASSERT(subTileIndex >= 0 && subTileIndex < 8);

			float ndcDepthValue = reinterpret_cast<const float*>(&L0MaxDepthValue)[subTileIndex];
			
			ndcDepthValue = (ndcDepthValue + 1.0f) * 0.5f;
			ndcDepthValue = ndcDepthValue * ndcDepthValue * ndcDepthValue;
			//const float linearDepth = (2.0 * Camera::GetMainCamera()->GetClippingPlaneNear() * Camera::GetMainCamera()->GetClippingPlaneFar()) / (Camera::GetMainCamera()->GetClippingPlaneFar() + Camera::GetMainCamera()->GetClippingPlaneNear() - ndcDepthValue * (Camera::GetMainCamera()->GetClippingPlaneFar() - Camera::GetMainCamera()->GetClippingPlaneNear()));

			//const float nonLinearDepthValue = ((1.0f / linearDepth) - (1.0f / Camera::GetMainCamera()->GetClippingPlaneNear())) / ((1.0f / Camera::GetMainCamera()->GetClippingPlaneFar()) - (1.0f / Camera::GetMainCamera()->GetClippingPlaneNear()));

			

			dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DBox
			(
				math::Vector3(DEBUGGER_TILE_BOX_PADIDNG_X + -1.0f + xScale * subTileColIndex, DEBUGGER_TILE_BOX_PADIDNG_Y + -1.0f + yScale * subTileRowIndex, 0.0f),
				math::Vector3(-DEBUGGER_TILE_BOX_PADIDNG_X + -1.0f + xScale * (subTileColIndex + 1), -DEBUGGER_TILE_BOX_PADIDNG_Y + -1.0f + yScale * (subTileRowIndex + 1), 0.0f),
				math::Vector4(ndcDepthValue, ndcDepthValue, ndcDepthValue, 1.0f)
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

	const float xScale = 2.0f / (float)(depthBuffer->mResolution.mColumnTileCount);
	const float yScale = 2.0f / (float)(depthBuffer->mResolution.mRowTileCount);

	for (size_t y = 0; y < depthBuffer->mResolution.mRowTileCount; y++)
	{
		// y = 0 -> bottom
		for (size_t x = 0; x < depthBuffer->mResolution.mColumnTileCount; x++)
		{
			const culling::Tile* const tile = depthBuffer->GetTile(y, x);

			//draw -1 ~ 1
			dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DBox
			(
				math::Vector3(DEBUGGER_TILE_BOX_PADIDNG_X + -1.0f + xScale * x, DEBUGGER_TILE_BOX_PADIDNG_Y + -1.0f + yScale * y, 0.0f),
				math::Vector3(-DEBUGGER_TILE_BOX_PADIDNG_X + -1.0f + xScale * (x + 1), -DEBUGGER_TILE_BOX_PADIDNG_Y + -1.0f + yScale * (y + 1), 0.0f),
				depthBuffer->GetTile(y, x)->GetIsTriangleBinned() == true ? eColor::Red : eColor::White
			);
		}
	}

}
