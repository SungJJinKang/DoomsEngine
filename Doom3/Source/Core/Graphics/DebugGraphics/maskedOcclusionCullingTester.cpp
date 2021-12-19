#include "maskedOcclusionCullingTester.h"

#include "imgui.h"
#include <EngineGUI/PrintText.h>

void dooms::graphics::maskedOcclusionCullingTester::DebugBinnedTriangles
(
	const culling::Tile* const tiles,
	const size_t tileCount
)
{
	std::atomic_thread_fence(std::memory_order_acquire);

	for(size_t i = 0 ; i < tileCount ; i++)
	{
		dooms::ui::PrintText
		(
			"MaskedSWOcclusionCulling Tile Binned Triangle Count ( TileIndex %u ) : %u",
			i,
			tiles->mBinnedTriangles.mCurrentTriangleCount.load(std::memory_order_relaxed)
		);
	}
	
}
