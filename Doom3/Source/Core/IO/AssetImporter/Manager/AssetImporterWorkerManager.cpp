#include "AssetImporterWorkerManager.h"

#include "../AssetImporterWorker/AssetImporterWorkerForwardDeclaration.h"

#include "../AssetImporterWorker/AssetImporterWorker.h"
#include "../AssetImporterWorker/AssetImporterWorker_Audio.h"
#include "../AssetImporterWorker/AssetImporterWorker_Font.h"
#include "../AssetImporterWorker/AssetImporterWorker_Shader.h"
#include "../AssetImporterWorker/AssetImporterWorker_Text.h"
#include "../AssetImporterWorker/AssetImporterWorker_Texture.h"
#include "../AssetImporterWorker/AssetImporterWorker_Three_D_Model.h"

void assetImporter::AssetImporterWorkerManager::InitializeAssetImporterWorkersStatic()
{
	doom::assetImporter::AssetImporterWorker_Audio::InitializeAssetImporterWorkerStatic();
	doom::assetImporter::AssetImporterWorker_Font::InitializeAssetImporterWorkerStatic();
	doom::assetImporter::AssetImporterWorker_Shader::InitializeAssetImporterWorkerStatic();
	doom::assetImporter::AssetImporterWorker_Text::InitializeAssetImporterWorkerStatic();
	doom::assetImporter::AssetImporterWorker_Texture::InitializeAssetImporterWorkerStatic();
	doom::assetImporter::AssetImporterWorker_THREE_D_MODEL::InitializeAssetImporterWorkerStatic();
}

doom::assetImporter::AssetImporterWorkerManager::AssetImporterWorkerManager()
{
	InitializeAssetImporterWorkersStatic();
}

doom::assetImporter::AssetImporterWorkerManager::~AssetImporterWorkerManager()
{
	ClearAssetImporterWorker();
}

doom::assetImporter::AssetImporterWorker* doom::assetImporter::AssetImporterWorkerManager::CreateAssetImporterWorker
(
	const doom::asset::eAssetType eAssetType
)
{
	doom::assetImporter::AssetImporterWorker* createdAssetImporterWorkder = nullptr;

	switch(eAssetType)
	{

	case doom::asset::eAssetType::AUDIO:
		
		createdAssetImporterWorkder = doom::CreateDObject<doom::assetImporter::AssetImporterWorker_Audio>();
		break;

	case doom::asset::eAssetType::FONT:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetImporter::AssetImporterWorker_Font>();
		break;

	case doom::asset::eAssetType::SHADER:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetImporter::AssetImporterWorker_Shader>();
		break;

	case doom::asset::eAssetType::TEXT:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetImporter::AssetImporterWorker_Text>();
		break;

	case doom::asset::eAssetType::TEXTURE:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetImporter::AssetImporterWorker_Texture>();
		break;

	case doom::asset::eAssetType::THREE_D_MODEL:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetImporter::AssetImporterWorker_THREE_D_MODEL>();
		break;

	default:
		NEVER_HAPPEN;

	}
	D_ASSERT(createdAssetImporterWorkder != nullptr);
	
	return createdAssetImporterWorkder;
}


void doom::assetImporter::AssetImporterWorkerManager::EnqueueWorker
(
	doom::assetImporter::AssetImporterWorker* const assetImporterWorker)
{
	D_ASSERT(assetImporterWorker != nullptr);

	const doom::asset::eAssetType assetTypeEnum = assetImporterWorker->GetEAssetType();
	mAssetApiImportersQueue[static_cast<UINT32>(assetTypeEnum)].enqueue(assetImporterWorker);
}

doom::assetImporter::AssetImporterWorker* assetImporter::AssetImporterWorkerManager::DequeueWorker
(
	const doom::asset::eAssetType eAssetType
)
{
	doom::assetImporter::AssetImporterWorker* assetImporterWorker = nullptr;

	while(assetImporterWorker == nullptr)
	{
		mAssetApiImportersQueue[static_cast<size_t>(eAssetType)].try_dequeue(assetImporterWorker);

		if(assetImporterWorker != nullptr)
		{
			break;
		}

		if (mAssetApiImportersCount[static_cast<size_t>(eAssetType)].load() >= MAX_ASSETIMPORTER_WORKER_COUNT)
		{
			mAssetApiImportersQueue[static_cast<size_t>(eAssetType)].wait_dequeue(assetImporterWorker);
		}
		else
		{
			mAssetApiImportersCount[static_cast<size_t>(eAssetType)]++;
			assetImporterWorker = CreateAssetImporterWorker(eAssetType);
		
		}
	}

	D_ASSERT(assetImporterWorker != nullptr);

	return assetImporterWorker;
}


void doom::assetImporter::AssetImporterWorkerManager::ClearAssetImporterWorker()
{
	for(UINT32 assetTypeIndex = 0 ; assetTypeIndex < doom::asset::ENUM_ASSETTYPE_COUNT ; assetTypeIndex++)
	{
		doom::assetImporter::AssetImporterWorker* temp = nullptr;
		while (mAssetApiImportersCount[assetTypeIndex].load() > 0)
		{
			mAssetApiImportersQueue[assetTypeIndex].wait_dequeue(temp);
			if(temp != nullptr)
			{
				delete temp;
				mAssetApiImportersCount[assetTypeIndex]--;
			}
		}
		D_DEBUG_LOG("Clear ApiImporterQueue ");

	}
}

