#pragma once

#include <array>

#include "../Core.h"
#include "Layer.h"
#include "IWorldIndependent.h"

namespace doom
{
	class SharedWorldSetting : public ISingleton<SharedWorldSetting>, public IWorldIndependent
	{
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

		SharedWorldSetting()
		{
			for (unsigned int i = 0; i < mReservedLayerName.size(); i++)
			{
				mLayers[i].mLayerName = mReservedLayerName[i];
			}
		}

	};
	extern SharedWorldSetting mSharedWorldSetting;


}