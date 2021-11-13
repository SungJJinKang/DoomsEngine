#pragma once

#include <array>

#include "../Core.h"
#include "Layer.h"
#include "IWorldIndependent.h"

#include "SharedSceneSetting.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS SharedSceneSetting : public DObject, public ISingleton<SharedSceneSetting>, public I_IndependentFromScene
	{
		GENERATE_BODY()
		

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