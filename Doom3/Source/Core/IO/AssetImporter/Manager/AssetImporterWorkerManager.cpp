#include "AssetImporterWorkerManager.h"

#include "../AssetImporterWorker/AssetImporterWorker.h"

#include "../AssetImporterWorker/AssetImporterWorker_Audio.h"
#include "../AssetImporterWorker/AssetImporterWorker_Font.h"
#include "../AssetImporterWorker/AssetImporterWorker_Shader.h"
#include "../AssetImporterWorker/AssetImporterWorker_Text.h"
#include "../AssetImporterWorker/AssetImporterWorker_Texture.h"
#include "../AssetImporterWorker/AssetImporterWorker_Three_D_Model.h"

doom::assetimporter::AssetImporterWorkerManager::AssetImporterWorkerManager() = default;
doom::assetimporter::AssetImporterWorkerManager::~AssetImporterWorkerManager()
{
	ClearAssetImporterWorker();
}
doom::assetimporter::AssetImporterWorkerManager::AssetImporterWorkerManager(AssetImporterWorkerManager&&) noexcept = default;
doom::assetimporter::AssetImporterWorkerManager& doom::assetimporter::AssetImporterWorkerManager::operator=(AssetImporterWorkerManager&&) noexcept = default;


doom::assetimporter::AssetImporterWorker* doom::assetimporter::AssetImporterWorkerManager::CreateAssetImporterWorker
(
	const doom::asset::eAssetType eAssetType)
{

	doom::assetimporter::AssetImporterWorker* createdAssetImporterWorkder = nullptr;

	switch(eAssetType)
	{

	case doom::asset::eAssetType::AUDIO:
		
		createdAssetImporterWorkder = new doom::assetimporter::AssetImporterWorker_Audio();
		break;

	case doom::asset::eAssetType::FONT:
		
		createdAssetImporterWorkder = new doom::assetimporter::AssetImporterWorker_Font();
		break;

	case doom::asset::eAssetType::SHADER:
		
		createdAssetImporterWorkder = new doom::assetimporter::AssetImporterWorker_Shader();
		break;

	case doom::asset::eAssetType::TEXT:
		
		createdAssetImporterWorkder = new doom::assetimporter::AssetImporterWorker_Text();
		break;

	case doom::asset::eAssetType::TEXTURE:
		
		createdAssetImporterWorkder = new doom::assetimporter::AssetImporterWorker_Texture();
		break;

	case doom::asset::eAssetType::THREE_D_MODEL:
		
		createdAssetImporterWorkder = new doom::assetimporter::AssetImporterWorker_THREE_D_MODEL();
		break;

	}
	D_ASSERT(createdAssetImporterWorkder != nullptr);

	mCreatedAssetApiImporters[static_cast<size_t>(eAssetType)].emplace_back(createdAssetImporterWorkder);

	return createdAssetImporterWorkder;
}


void doom::assetimporter::AssetImporterWorkerManager::EnqueueWorker
(
	doom::assetimporter::AssetImporterWorker* const assetImporterWorker)
{
	D_ASSERT(assetApiImporter != nullptr);

	const doom::asset::eAssetType assetTypeEnum = assetImporterWorker->GetEAssetType();
	mAssetApiImportersQueue[static_cast<size_t>(assetTypeEnum)].enqueue(assetImporterWorker);
}

doom::assetimporter::AssetImporterWorker* assetimporter::AssetImporterWorkerManager::DequeueWorker
(
	const doom::asset::eAssetType eAssetType
)
{
	doom::assetimporter::AssetImporterWorker* assetImporterWorker = nullptr;

	const bool IsDequeueSuccess = mAssetApiImportersQueue[static_cast<size_t>(eAssetType)].try_dequeue(assetImporterWorker);
	if(IsDequeueSuccess == false)
	{//Queue is empty
		assetImporterWorker = CreateAssetImporterWorker(eAssetType);
	}

	return assetImporterWorker;
}


void doom::assetimporter::AssetImporterWorkerManager::ClearAssetImporterWorker()
{
	for(std::vector<std::unique_ptr<doom::assetimporter::AssetImporterWorker>>& workerList : mCreatedAssetApiImporters)
	{
		for(std::unique_ptr<doom::assetimporter::AssetImporterWorker>& worker : workerList)
		{
			worker.reset(nullptr);
		}
	}

	for(auto& importerWorkerQueue: mAssetApiImportersQueue)
	{
		doom::assetimporter::AssetImporterWorker* temp{};
		while (importerWorkerQueue.try_dequeue(temp))
		{
		}
		D_DEBUG_LOG("Clear ApiImporterQueue ");
	}
}

