#include "MaskedOcclusionCulliingDebugger.h"

#include <Rendering/Graphics_Server.h>
#include "imgui/imgui.h"
#include <Rendering/Culling/EveryCulling/CullingModule/MaskedSWOcclusionCulling/MaskedSWOcclusionCulling.h>


UINT32 dooms::ui::MaskedOcclusionCulliingDebugger::GetColumnTileCount()
{
	return mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mColumnTileCount;
}

UINT32 dooms::ui::MaskedOcclusionCulliingDebugger::GetRowTileCount()
{
	return mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mRowTileCount;
}

UINT32 dooms::ui::MaskedOcclusionCulliingDebugger::GetColumnSubTileCount()
{
	return mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mColumnSubTileCount;
}

UINT32 dooms::ui::MaskedOcclusionCulliingDebugger::GetRowSubTileCount()
{
	return mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mRowSubTileCount;
}

void dooms::ui::MaskedOcclusionCulliingDebugger::RenderL0MaxDepthValue()
{
	if (mMaskedSWOcclusionCulling != nullptr)
	{
		const ImVec4 redColor{ 1.0f, 0.0f, 0.0f, 1.0f };
		const ImVec4 whiteColor{ 1.0f, 1.0f, 1.0f, 1.0f };


		const UINT32 screenWidth = mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mWidth;
		const UINT32 screenHeight = mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mHeight;

		//const UINT32 space = ((float)screenWidth / (float)screenHeight) * ((float)GetRowSubTileCount() / (float)GetColumnSubTileCount());

		for (INT32 subTileRowIndex = static_cast<INT32>(GetRowSubTileCount()) - 1; subTileRowIndex >= 0; subTileRowIndex--)
		{
			for (INT32 subTileColIndex = 0; subTileColIndex < static_cast<INT32>(GetColumnSubTileCount()); subTileColIndex++)
			{
				const INT32 tileRowIndex = subTileRowIndex / (TILE_HEIGHT / SUB_TILE_HEIGHT);
				const INT32 tileColIndex = subTileColIndex / (TILE_WIDTH / SUB_TILE_WIDTH);

				const INT32 subTileRowIndexInTile = subTileRowIndex % (TILE_HEIGHT / SUB_TILE_HEIGHT);
				const INT32 subTileColIndexInTile = subTileColIndex % (TILE_WIDTH / SUB_TILE_WIDTH);

				D_ASSERT(subTileRowIndexInTile >= 0 && subTileRowIndexInTile < (TILE_HEIGHT / SUB_TILE_HEIGHT));
				D_ASSERT(subTileColIndexInTile >= 0 && subTileRowIndexInTile < (TILE_WIDTH / SUB_TILE_WIDTH));

				const culling::M256F L0MaxDepthValue = mMaskedSWOcclusionCulling->mDepthBuffer.GetTile(tileRowIndex, tileColIndex)->mHizDatas.L0SubTileMaxDepthValue;
				const INT32 subTileIndex = subTileColIndexInTile + subTileRowIndexInTile * (TILE_WIDTH / SUB_TILE_WIDTH);
				D_ASSERT(subTileIndex >= 0 && subTileIndex < 8);

				const float subTileL0MaxDepthValue = reinterpret_cast<const float*>(&L0MaxDepthValue)[subTileIndex];

				ImGui::Text("%f", subTileL0MaxDepthValue);

				if (subTileColIndex != (GetColumnSubTileCount() - 1))
				{
					ImGui::SameLine(0, 15);
				}
			}
		}
	}
}

void dooms::ui::MaskedOcclusionCulliingDebugger::RenderBinnedTriangles()
{
	D_ASSERT(mMaskedSWOcclusionCulling != nullptr);

	if (mMaskedSWOcclusionCulling != nullptr)
	{
		const ImVec4 redColor{ 1.0f, 0.0f, 0.0f, 1.0f };
		const ImVec4 whiteColor{ 1.0f, 1.0f, 1.0f, 1.0f };


		const UINT32 screenWidth = mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mWidth;
		const UINT32 screenHeight = mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mHeight;

		//const UINT32 space = ((float)screenWidth / (float)screenHeight) * ((float)GetRowTileCount() / (float)GetColumnTileCount());

		for (INT32 rowIndex = static_cast<INT32>(GetRowTileCount()) - 1; rowIndex >= 0; rowIndex--)
		{
			for (INT32 colIndex = 0; colIndex < static_cast<INT32>(GetColumnTileCount()); colIndex++)
			{
				const bool isTriangleBinned = mMaskedSWOcclusionCulling->mDepthBuffer.GetTile(rowIndex, colIndex)->mBinnedTriangleCount > 0;
				if (isTriangleBinned == true)
				{
					ImGui::TextColored(redColor, "O");
				}
				else
				{
					ImGui::TextColored(whiteColor, "X");
				}

				if (colIndex != (GetColumnTileCount() - 1))
				{
					ImGui::SameLine(0, 15);
				}
			}
		}
	}
}

void dooms::ui::MaskedOcclusionCulliingDebugger::Init()
{
	Base::Init();
}

void dooms::ui::MaskedOcclusionCulliingDebugger::Render()
{
	if (ImGui::Begin("Masked SW Occlusion Culling Debugger ( Binned Triangle Count of Tile )"))
	{
		RenderBinnedTriangles();
	}
	ImGui::End();

	if (ImGui::Begin("Masked SW Occlusion Culling Debugger ( L0 Max Depth Value of SubTile )"))
	{
		RenderL0MaxDepthValue();
	}
	ImGui::End();
	
}

void dooms::ui::MaskedOcclusionCulliingDebugger::SetMaskedSWOcclusionCulling
(
	culling::MaskedSWOcclusionCulling* const culling
)
{
	mMaskedSWOcclusionCulling = culling;
}
