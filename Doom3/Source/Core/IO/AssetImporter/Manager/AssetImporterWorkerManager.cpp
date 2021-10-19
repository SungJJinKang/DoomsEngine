#include "AssetImporterWorkerManager.h"

#include "../AssetImporterWorker/AssetImporterWorkerForwardDeclaration.h"

#include "../AssetImporterWorker/AssetImporterWorker.h"
#include "../AssetImporterWorker/AssetImporterWorker_Audio.h"
#include "../AssetImporterWorker/AssetImporterWorker_Font.h"
#include "../AssetImporterWorker/AssetImporterWorker_Shader.h"
#include "../AssetImporterWorker/AssetImporterWorker_Text.h"
#include "../AssetImporterWorker/AssetImporterWorker_Texture.h"
#include "../AssetImporterWorker/AssetImporterWorker_Three_D_Model.h"

void assetimporter::AssetImporterWorkerManager::InitializeAssetImporterWorkersStatic()
{
	doom::assetimporter::AssetImporterWorker_Audio::InitializeAssetImporterWorkerStatic();
	doom::assetimporter::AssetImporterWorker_Font::InitializeAssetImporterWorkerStatic();
	doom::assetimporter::AssetImporterWorker_Shader::InitializeAssetImporterWorkerStatic();
	doom::assetimporter::AssetImporterWorker_Text::InitializeAssetImporterWorkerStatic();
	doom::assetimporter::AssetImporterWorker_Texture::InitializeAssetImporterWorkerStatic();
	doom::assetimporter::AssetImporterWorker_THREE_D_MODEL::InitializeAssetImporterWorkerStatic();
}

doom::assetimporter::AssetImporterWorkerManager::AssetImporterWorkerManager()
{
	InitializeAssetImporterWorkersStatic();
}

doom::assetimporter::AssetImporterWorkerManager::~AssetImporterWorkerManager()
{
	ClearAssetImporterWorker();
}

doom::assetimporter::AssetImporterWorker* doom::assetimporter::AssetImporterWorkerManager::CreateAssetImporterWorker
(
	const doom::asset::eAssetType eAssetType
)
{
	doom::assetimporter::AssetImporterWorker* createdAssetImporterWorkder = nullptr;

	switch(eAssetType)
	{

	case doom::asset::eAssetType::AUDIO:
		
		createdAssetImporterWorkder = doom::CreateDObject<doom::assetimporter::AssetImporterWorker_Audio>();
		break;

	case doom::asset::eAssetType::FONT:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetimporter::AssetImporterWorker_Font>();
		break;

	case doom::asset::eAssetType::SHADER:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetimporter::AssetImporterWorker_Shader>();
		break;

	case doom::asset::eAssetType::TEXT:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetimporter::AssetImporterWorker_Text>();
		break;

	case doom::asset::eAssetType::TEXTURE:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetimporter::AssetImporterWorker_Texture>();
		break;

	case doom::asset::eAssetType::THREE_D_MODEL:
		
		createdAssetImporterWorkder = doom::CreateDObject < doom::assetimporter::AssetImporterWorker_THREE_D_MODEL>();
		break;

	default:
		NEVER_HAPPEN;

	}
	D_ASSERT(createdAssetImporterWorkder != nullptr);
	
	return createdAssetImporterWorkder;
}


void doom::assetimporter::AssetImporterWorkerManager::EnqueueWorker
(
	doom::assetimporter::AssetImporterWorker* const assetImporterWorker)
{
	D_ASSERT(assetImporterWorker != nullptr);

	const doom::asset::eAssetType assetTypeEnum = assetImporterWorker->GetEAssetType();
	mAssetApiImportersQueue[static_cast<UINT32>(assetTypeEnum)].enqueue(assetImporterWorker);
}

doom::assetimporter::AssetImporterWorker* assetimporter::AssetImporterWorkerManager::DequeueWorker
(
	const doom::asset::eAssetType eAssetType
)
{
	doom::assetimporter::AssetImporterWorker* assetImporterWorker = nullptr;

	while(assetImporterWorker == nullptr)
	{
		mAssetApiImportersQueue[static_cast<SIZE_T>(eAssetType)].try_dequeue(assetImporterWorker);

		if(assetImporterWorker != nullptr)
		{
			break;
		}

		if (mAssetApiImportersCount[static_cast<SIZE_T>(eAssetType)].load() >= MAX_ASSETIMPORTER_WORKER_COUNT)
		{
			mAssetApiImportersQueue[static_cast<SIZE_T>(eAssetType)].wait_dequeue(assetImporterWorker);
		}
		else
		{
			mAssetApiImportersCount[static_cast<SIZE_T>(eAssetType)]++;
			assetImporterWorker = CreateAssetImporterWorker(eAssetType);
		
		}
	}

	D_ASSERT(assetImporterWorker != nullptr);

	return assetImporterWorker;
}


void doom::assetimporter::AssetImporterWorkerManager::ClearAssetImporterWorker()
{
	for(UINT32 assetTypeIndex = 0 ; assetTypeIndex < doom::asset::ENUM_ASSETTYPE_COUNT ; assetTypeIndex++)
	{
		doom::assetimporter::AssetImporterWorker* temp = nullptr;
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

