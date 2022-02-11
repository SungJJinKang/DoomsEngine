#pragma once

#include <Core.h>

#include <vector>
#include "Layer.h"

#include "LayerManager.reflection.h"
namespace dooms
{
	class D_CLASS LayerManager : public DObject
	{
		GENERATE_BODY()

	private:

		D_PROPERTY()
		std::vector<Layer> mLayers;

		void RefreshLayerIndex();

	public:

		void Initialize();

		bool PushLayer(const char* const layerName);
		bool PushLayer(const char* const layerName, const UINT32 targetIndex);
		bool PopLayer();
		bool RemoveLayer(const UINT32 index);

	};

}

