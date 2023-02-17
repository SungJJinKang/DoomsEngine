#pragma once

#include <Core.h>

#include "../EngineGUIModule.h"
#include <SingleTon/Singleton.h>

#include "MaskedOcclusionCulliingDebugger.reflection.h"
namespace culling
{
	class MaskedSWOcclusionCulling;
}


namespace dooms
{
	namespace ui
	{
		class D_CLASS MaskedOcclusionCulliingDebugger : public EngineGUIModule, public ISingleton<MaskedOcclusionCulliingDebugger>
		{
			GENERATE_BODY()
		private:

			culling::MaskedSWOcclusionCulling* mMaskedSWOcclusionCulling = nullptr;

			UINT32 GetColumnTileCount();
			UINT32 GetRowTileCount();
			UINT32 GetColumnSubTileCount();
			UINT32 GetRowSubTileCount();
			void RenderL0MaxDepthValue();
			void RenderBinnedTriangles();

		public:

			void Init() override;
			void Render() override;
			void SetMaskedSWOcclusionCulling(culling::MaskedSWOcclusionCulling* const culling);
		};
	}
}
