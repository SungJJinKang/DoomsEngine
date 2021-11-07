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
	dooms::assetImporter::AssetImporterWorker_Audio::InitializeAssetImporterWorkerStatic();
	dooms::assetImporter::AssetImporterWorker_Font::InitializeAssetImporterWorkerStatic();
	dooms::assetImporter::AssetImporterWorker_Shader::InitializeAssetImporterWorkerStatic();
	dooms::assetImporter::AssetImporterWorker_Text::InitializeAssetImporterWorkerStatic();
	dooms::assetImporter::AssetImporterWorker_Texture::InitializeAssetImporterWorkerStatic();
	dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL::InitializeAssetImporterWorkerStatic();
}

dooms::assetImporter::AssetImporterWorkerManager::AssetImporterWorkerManager()
{
	InitializeAssetImporterWorkersStatic();
}

dooms::assetImporter::AssetImporterWorkerManager::~AssetImporterWorkerManager()
{
	ClearAssetImporterWorker();
}

dooms::assetImporter::AssetImporterWorker* dooms::assetImporter::AssetImporterWorkerManager::CreateAssetImporterWorker
(
	const dooms::asset::eAssetType eAssetType
)
{
	dooms::assetImporter::AssetImporterWorker* createdAssetImporterWorkder = nullptr;

	switch(eAssetType)
	{

	case dooms::asset::eAssetType::AUDIO:
		
		createdAssetImporterWorkder = dooms::CreateDObject<dooms::assetImporter::AssetImporterWorker_Audio>();
		break;

	case dooms::asset::eAssetType::FONT:
		
		createdAssetImporterWorkder = dooms::CreateDObject < dooms::assetImporter::AssetImporterWorker_Font>();
		break;

	case dooms::asset::eAssetType::SHADER:
		
		createdAssetImporterWorkder = dooms::CreateDObject < dooms::assetImporter::AssetImporterWorker_Shader>();
		break;

	case dooms::asset::eAssetType::TEXT:
		
		createdAssetImporterWorkder = dooms::CreateDObject < dooms::assetImporter::AssetImporterWorker_Text>();
		break;

	case dooms::asset::eAssetType::TEXTURE:
		
		createdAssetImporterWorkder = dooms::CreateDObject < dooms::assetImporter::AssetImporterWorker_Texture>();
		break;

	case dooms::asset::eAssetType::THREE_D_MODEL:
		
		createdAssetImporterWorkder = dooms::CreateDObject < dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL>();
		break;

	default:
		NEVER_HAPPEN;

	}
	D_ASSERT(createdAssetImporterWorkder != nullptr);
	
	return createdAssetImporterWorkder;
}


void dooms::assetImporter::AssetImporterWorkerManager::EnqueueWorker
(
	dooms::assetImporter::AssetImporterWorker* const assetImporterWorker)
{
	D_ASSERT(assetImporterWorker != nullptr);

	const dooms::asset::eAssetType assetTypeEnum = assetImporterWorker->GetEAssetType();
	mAssetApiImportersQueue[static_cast<UINT32>(assetTypeEnum)].enqueue(assetImporterWorker);
}

dooms::assetImporter::AssetImporterWorker* assetImporter::AssetImporterWorkerManager::DequeueWorker
(
	const dooms::asset::eAssetType eAssetType
)
{
	dooms::assetImporter::AssetImporterWorker* assetImporterWorker = nullptr;

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


void dooms::assetImporter::AssetImporterWorkerManager::ClearAssetImporterWorker()
{
	for(UINT32 assetTypeIndex = 0 ; assetTypeIndex < dooms::asset::ENUM_ASSETTYPE_COUNT ; assetTypeIndex++)
	{
		dooms::assetImporter::AssetImporterWorker* temp = nullptr;
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

