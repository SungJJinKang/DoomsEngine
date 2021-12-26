#include "maskedOcclusionCullingTester.h"

#include "imgui.h"
#include <EngineGUI/PrintText.h>
#include <Graphics/DebugGraphics/DebugDrawer.h>
#include <Graphics/Graphics_Setting.h>

#define DEBUGGER_TILE_BOX_PADIDNG 0.001f

void dooms::graphics::maskedOcclusionCullingTester::DebugTileCoverageMask
(
	const culling::SWDepthBuffer* const depthBuffer
)
{
	std::atomic_thread_fence(std::memory_order_acquire);

	const float xScale = 2.0f / (float)(depthBuffer->mResolution.mColumnTileCount);
	const float yScale = 2.0f / (float)(depthBuffer->mResolution.mRowTileCount);

    for(size_t y = 0 ; y < depthBuffer->mResolution.mRowTileCount ; y++)
    {
		// y = 0 -> bottom
		for (size_t x = 0; x < depthBuffer->mResolution.mColumnTileCount; x++)
		{
			const culling::Tile* const tile = depthBuffer->GetTile(y, x);

			//draw -1 ~ 1
			dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DBox
			(
				math::Vector3(DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * x, DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * y, 1.0f),
				math::Vector3(-DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * (x + 1), -DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * (y + 1), 1.0f),
				(_mm256_testc_si256(tile->mHizDatas.l1CoverageMask, _mm256_set1_epi64x(0xFFFFFFFFFFFFFFFF)) == 1) ? eColor::Red : eColor::White // draw red when all bits of coverage mask is 1
				//(_mm256_testz_si256(tile->mHizDatas.l1CoverageMask, _mm256_set1_epi64x(0xFFFFFFFFFFFFFFFF)) == 0) ? eColor::Red : eColor::White // draw red when all bits of coverage mask is 1
			);

			/*
			for(size_t i = 0 ; i < tile->mBinnedTriangles.mCurrentTriangleCount ; i++)
			{

				math::Vector3 point1 = *reinterpret_cast<const math::Vector3*>(tile->mBinnedTriangles.mTriangleList[i].Points + 0);
				math::Vector3 point2 = *reinterpret_cast<const math::Vector3*>(tile->mBinnedTriangles.mTriangleList[i].Points + 1);
				math::Vector3 point3 = *reinterpret_cast<const math::Vector3*>(tile->mBinnedTriangles.mTriangleList[i].Points + 2);

				point1 /= math::Vector3(dooms::graphics::Graphics_Setting::GetScreenWidth(), dooms::graphics::Graphics_Setting::GetScreenHeight(), 1.0f);
				point2 /= math::Vector3(dooms::graphics::Graphics_Setting::GetScreenWidth(), dooms::graphics::Graphics_Setting::GetScreenHeight(), 1.0f);
				point3 /= math::Vector3(dooms::graphics::Graphics_Setting::GetScreenWidth(), dooms::graphics::Graphics_Setting::GetScreenHeight(), 1.0f);

				point1 *= 2.0f;
				point2 *= 2.0f;
				point3 *= 2.0f;

				point1 -= 1.0f;
				point2 -= 1.0f;
				point3 -= 1.0f;

				point1.z = 0.1f;
				point2.z = 0.1f;
				point3.z = 0.1f;

				dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DLine
				(
					point1,
					point2,
					eColor::Blue
				);

				dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DLine
				(
					point1,
					point3,
					eColor::Blue
				);

				dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DLine
				(
					point2,
					point3,
					eColor::Blue
				);
			}
			*/


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

			const culling::M256F L0MaxDepthValue = depthBuffer->GetTile(tileRowIndex, tileColIndex)->mHizDatas.L0MaxDepthValue;
			const INT32 subTileIndex = subTileColIndexInTile + subTileRowIndexInTile * (TILE_WIDTH / SUB_TILE_WIDTH);
			D_ASSERT(subTileIndex >= 0 && subTileIndex < 8);

			const float subTileL0MaxDepthValue = reinterpret_cast<const float*>(&L0MaxDepthValue)[subTileIndex];

			dooms::graphics::DebugDrawer::GetSingleton()->DebugDraw2DBox
			(
				math::Vector3(DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * subTileColIndex, DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * subTileRowIndex, 0.0f),
				math::Vector3(-DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * (subTileColIndex + 1), -DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * (subTileRowIndex + 1), 0.0f),
				math::Vector4((subTileL0MaxDepthValue + 1.0f) / 2.0f, 0.0f, 0.0f, 1.0f)
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
				math::Vector3(DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * x, DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * y, 0.0f),
				math::Vector3(-DEBUGGER_TILE_BOX_PADIDNG + -1.0f + xScale * (x + 1), -DEBUGGER_TILE_BOX_PADIDNG + -1.0f + yScale * (y + 1), 0.0f),
				depthBuffer->GetTile(y, x)->mBinnedTriangles.mCurrentTriangleCount > 0 ? eColor::Red : eColor::White
			);
		}
	}

}
