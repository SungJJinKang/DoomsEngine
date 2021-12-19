#include "maskedOcclusionCullingTester.h"

#include "imgui.h"
#include <EngineGUI/PrintText.h>

void dooms::graphics::maskedOcclusionCullingTester::DebugBinnedTriangles
(
	const culling::Tile* const tiles,
	const size_t tileCount
)
{
	for(size_t i = 0 ; i < tileCount ; i++)
	{
		dooms::ui::PrintText
		(
			"MaskedSWOcclusionCulling Tile Binned Triangle Count ( TileIndex %u ) : %u",
			i,
			tiles->mBinnedTriangles.mCurrentTriangleCount.load()
		);
	}
	
}
