#pragma once

#include <array>

#include "../Core.h"
#include "Layer.h"
#include "IWorldIndependent.h"

namespace dooms
{
	class DOOM_API SharedSceneSetting : public DObject, public ISingleton<SharedSceneSetting>, public I_IndependentFromScene
	{
		DOBJECT_CLASS_BODY(SharedSceneSetting, dooms::eDOBJECT_ClassFlags::NonCopyable);
		DOBJECT_CLASS_BASE_CHAIN(DObject)

	private:
		std::array<Layer, MAX_LAYER_COUNT> mLayers;

		std::array<std::string, RESERVED_LAYER_COUNT> mReservedLayerName
		{
			"Default",
			"",
			"TransparentFX",
			"IgnoreRaycast",
			"",
			"Water",
			"UI"

		};
	public:

		SharedSceneSetting()
		{
			for (UINT32 i = 0; i < mReservedLayerName.size(); i++)
			{
				mLayers[i].mLayerName = mReservedLayerName[i];
			}
		}

	};

}