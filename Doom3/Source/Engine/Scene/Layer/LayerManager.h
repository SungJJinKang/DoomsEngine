#pragma once

#include <Core.h>

#include <vector>
#include "Layer.h"
#include <SingleTon/Singleton.h>

#include "LayerManager.reflection.h"
namespace dooms
{
	class D_CLASS LayerManager : public DObject, public ISingleton<LayerManager>
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
		UINT32 GetLayerCount() const;

	};

}

