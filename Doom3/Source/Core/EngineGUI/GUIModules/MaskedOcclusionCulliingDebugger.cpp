#include "MaskedOcclusionCulliingDebugger.h"

#include <vector>
#include <Graphics/Graphics_Server.h>

#include "imgui.h"
#include "Graphics/Acceleration/LinearData_ViewFrustumCulling/CullingModule/MaskedSWOcclusionCulling/MaskedSWOcclusionCulling.h"

#define DEFAULT_SPACE_OFFSET 30

namespace dooms::ui::maskedOcclusionCulliingDebugger
{
	std::vector<std::vector<UINT32>> BinnedTriangleCount;

	extern UINT32 GetColumnCount()
	{
		return BinnedTriangleCount[0].size();
	}

	extern UINT32 GetRowCount()
	{
		return BinnedTriangleCount.size();
	}

	void extern RenderBinnedTriangles()
	{
		const ImVec4 redColor{ 1.0f, 0.0f, 0.0f, 1.0f };
		const ImVec4 whiteColor{ 1.0f, 1.0f, 1.0f, 1.0f };

		const std::uint32_t screenWidth = graphics::Graphics_Server::GetSingleton()->mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mWidth;
		const std::uint32_t screenHeight = graphics::Graphics_Server::GetSingleton()->mCullingSystem->mMaskedSWOcclusionCulling->mDepthBuffer.mResolution.mHeight;

		const std::uint32_t space = ((float)screenWidth / (float)screenHeight) * ((float)BinnedTriangleCount.size() / (float)BinnedTriangleCount[0].size());
		
		for (std::int32_t rowIndex = BinnedTriangleCount.size() - 1; rowIndex >= 0 ; rowIndex--)
		{
			for (std::int32_t colIndex = 0; colIndex < BinnedTriangleCount[0].size(); colIndex++)
			{
				const size_t triangleCount = BinnedTriangleCount[rowIndex][colIndex];
				if(triangleCount > 0)
				{
					ImGui::TextColored(redColor, "O");
				}
				else
				{
					ImGui::TextColored(whiteColor, "X");
				}

				if (colIndex != (BinnedTriangleCount[0].size() - 1))
				{
					ImGui::SameLine(0, space + DEFAULT_SPACE_OFFSET);
				}
			}
		}
	}
}

void dooms::ui::maskedOcclusionCulliingDebugger::Render()
{
	if (ImGui::Begin("Masked SW Occlusion Culling Debugger"))
	{
		RenderBinnedTriangles();
	}
	ImGui::End();
}

void dooms::ui::maskedOcclusionCulliingDebugger::InitializeBinTriangle
(
	const size_t rowCount,
	const size_t colCount
)
{
	BinnedTriangleCount.resize(rowCount);
	for(size_t rowIndex = 0 ; rowIndex < rowCount; rowIndex++)
	{
		BinnedTriangleCount[rowIndex].resize(colCount, 0);
	}
}

void dooms::ui::maskedOcclusionCulliingDebugger::SetBinnedTriangleCount
(
	const size_t rowIndex, 
	const size_t colIndex,
	const UINT32 triangleCount
)
{
	D_ASSERT(colIndex < GetColumnCount());
	D_ASSERT(rowIndex < GetRowCount());
	BinnedTriangleCount[rowIndex][colIndex] = triangleCount;
}

void dooms::ui::maskedOcclusionCulliingDebugger::SetBinnedTriangleCount
(
	const size_t tileIndex,
	const UINT32 triangleCount
)
{
	const size_t rowIndex = tileIndex / GetColumnCount();
	const size_t colIndex = tileIndex % GetColumnCount();
	SetBinnedTriangleCount(rowIndex, colIndex, triangleCount);
}
