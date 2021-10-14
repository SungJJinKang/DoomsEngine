#include "AssetImporter.h"

#include "Asset/Asset.h"

#include "Manager/AssetImporterWorkerManager.h"
#include <UI/PrintText.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>


const std::unordered_map<std::string, ::doom::asset::eAssetType> doom::assetimporter::AssetExtension
{
	//3D Model Asset Formats
	{".dae", ::doom::asset::eAssetType::THREE_D_MODEL},
	{ ".blend", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".bvh", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".3ds", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ase", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".obj", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".glFT", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ply", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".dxf", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ifc", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".nff", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".smd", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".vta", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl2", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl3", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".pk3", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdmdcl2", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".md5mesh", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".md5anim", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".md5camera ", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".q3o", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".q3s", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".raw", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ac", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".stl", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".dxf", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".irrmesh", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".irr", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".off", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".dterxf", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".hmp", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".mesh", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".skeleton", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".material", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ms3d", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".lwo", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".lws", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".lxo", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".csm", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".ply", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".cob", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".scn", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".fbx", ::doom::asset::eAssetType::THREE_D_MODEL },
	{ ".assbin", ::doom::asset::eAssetType::THREE_D_MODEL },

	//////////////////////////////////////////////////////////////////////////

	{ ".txt", ::doom::asset::eAssetType::TEXT },
	{ ".ini", ::doom::asset::eAssetType::TEXT },

	/////////////////////////////////////////////////////

	{ ".glsl", ::doom::asset::eAssetType::SHADER },

	/////////////////////////////////////////////////////////

	{ ".jpg", ::doom::asset::eAssetType::TEXTURE },
	{ ".jpeg", ::doom::asset::eAssetType::TEXTURE },
	{ ".png", ::doom::asset::eAssetType::TEXTURE },
	{ ".bmp", ::doom::asset::eAssetType::TEXTURE },
	{ ".tga", ::doom::asset::eAssetType::TEXTURE },
	//{ ".hdr", ::doom::asset::eAssetType::TEXTURE },
	{ ".dds", ::doom::asset::eAssetType::TEXTURE }
};

const std::unordered_map<::doom::asset::eAssetType, std::string>  doom::assetimporter::AssetInBuildExtension
{
	{::doom::asset::eAssetType::TEXTURE, ".dds"},
	{::doom::asset::eAssetType::THREE_D_MODEL, ".assbin"}

};

std::optional<::doom::asset::eAssetType>  doom::assetimporter::GetAssetType(const std::filesystem::path& path)
{
	if (path.has_extension())
	{
		auto citer = AssetExtension.find(path.extension().string());
		if (citer != AssetExtension.cend())
		{//find extenstion
			return citer->second;
		}
		else
		{
			return {};
		}
	}
	else
	{
		return {};
	}
}

bool doom::assetimporter::ImportAssetJob(std::filesystem::path path, doom::asset::Asset* const asset)
{
	const doom::asset::eAssetType assetType = asset->GetEAssetType();

	doom::assetimporter::AssetImporterWorker* const importerWorker = 
		doom::assetimporter::AssetImporterWorkerManager::GetSingleton()->DequeueWorker(assetType);

	D_ASSERT(importerWorker != nullptr);
	D_ASSERT(importerWorker->GetEAssetType() == asset->GetEAssetType());

	bool isSuccess = false;

	try
	{
		isSuccess = importerWorker->ImportSpecificAsset(path, asset);
	}
	catch (...)
	{
		

		std::exception_ptr p = std::current_exception();
		//std::clog << (p ? p._Current_exception(name() : "null") << std::endl;

		D_ASSERT(false);
	}


	if (isSuccess)
	{
		asset->SetAssetStatus(::doom::asset::Asset::AssetStatus::CompletlyImported);
		doom::ui::PrintText("Import Success : %s", path.string().c_str());
	}
	else
	{
		asset->SetAssetStatus(::doom::asset::Asset::AssetStatus::FailToImport);
	}

	doom::assetimporter::AssetImporterWorkerManager::GetSingleton()->EnqueueWorker(importerWorker);

	return isSuccess;

}

std::future<bool> doom::assetimporter::PushImportingAssetJobToThreadPool
(
	std::filesystem::path path,
	doom::asset::Asset* const asset
)
{
	std::function<bool()> newTask = std::bind(ImportAssetJob, std::move(path), asset);
	asset->SetAssetStatus(::doom::asset::Asset::AssetStatus::WaitingImport);

	return doom::resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(std::move(newTask));
}

std::vector<std::future<bool>> doom::assetimporter::PushImportingAssetJobToThreadPool
(
	const std::vector<std::filesystem::path>& paths, 
	const std::vector<doom::asset::Asset*>& assets
)
{
	D_ASSERT(paths.size() == assets.size());

	std::vector<std::function<bool()>> newTasks{};
	newTasks.reserve(paths.size());
	for (UINT32 i = 0; i < paths.size(); i++)
	{
		newTasks.push_back(std::bind(ImportAssetJob, std::move(paths[i]), assets[i]));
		assets[i]->SetAssetStatus(::doom::asset::Asset::AssetStatus::WaitingImport);
	}

	/// <summary>
			/// maybe will be copied
			/// </summary>
			/// <param name="paths"></param>
			/// <returns></returns>
	return resource::JobSystem::GetSingleton()->PushBackJobChunkToPriorityQueue(std::move(newTasks));
}

