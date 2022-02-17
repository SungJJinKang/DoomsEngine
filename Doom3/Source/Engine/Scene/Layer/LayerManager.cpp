#include "LayerManager.h"

#include "DefaultLayers.h"

void dooms::LayerManager::RefreshLayerIndex()
{
	for(UINT32 layerIndex = 0 ; layerIndex < mLayers.size() ; layerIndex++)
	{
		mLayers[layerIndex].mLayerIndex = layerIndex;
	}
}

void dooms::LayerManager::Initialize()
{
	std::vector<Layer> defaultLayers = defaultLayers::CreateDefaultLayers();

	mLayers.insert(mLayers.begin(), defaultLayers.begin(), defaultLayers.end());
}

bool dooms::LayerManager::PushLayer(const char* const layerName)
{
	mLayers.emplace_back();
	mLayers.back().mLayerName = layerName;
	RefreshLayerIndex();

	return true;
}

bool dooms::LayerManager::PushLayer(const char* const layerName, const UINT32 targetIndex)
{
	bool isSuccess = false;
	D_ASSERT(targetIndex <= mLayers.size());
	if (targetIndex <= mLayers.size())
	{
		auto iter = mLayers.insert(mLayers.begin() + targetIndex, Layer());
		iter->mLayerName = layerName;
		RefreshLayerIndex();

		isSuccess = true;
	}
	return isSuccess;
}


bool dooms::LayerManager::PopLayer()
{
	bool isSuccess = false;
	if(mLayers.empty() == false)
	{
		mLayers.pop_back();
		RefreshLayerIndex();

		isSuccess = true;
	}
	return isSuccess;
}

bool dooms::LayerManager::RemoveLayer(const UINT32 index)
{
	bool isSuccess = false;

	D_ASSERT(index < mLayers.size());
	if(index < mLayers.size())
	{
		mLayers.erase(mLayers.begin() + index);
		RefreshLayerIndex();

		isSuccess = true;
	}
	return isSuccess;
}

UINT32 dooms::LayerManager::GetLayerCount() const
{
	return mLayers.size();
}
