#include "MaskedOcclusionCulliingDebugger.h"

#include <vector>

#include "imgui.h"

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
		for (size_t rowIndex = 0; rowIndex < BinnedTriangleCount.size(); rowIndex++)
		{
			for (size_t colIndex = 0; colIndex < BinnedTriangleCount[0].size(); colIndex++)
			{

				ImGui::Text("%u", BinnedTriangleCount[rowIndex][colIndex]);
				if (colIndex != BinnedTriangleCount[0].size() - 1)
				{
					ImGui::SameLine(0, 3);
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
