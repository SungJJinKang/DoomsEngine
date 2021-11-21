#include "assetImporter.h"

#include "Asset/Asset.h"

#include "Manager/AssetImporterWorkerManager.h"
#include <EngineGUI/PrintText.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>


const std::unordered_map<std::string, ::dooms::asset::eAssetType> dooms::assetImporter::AssetExtension
{
	//3D Model Asset Formats
	{".dae", ::dooms::asset::eAssetType::THREE_D_MODEL},
	{ ".blend", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".bvh", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".3ds", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".ase", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".obj", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".glFT", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".ply", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".dxf", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".ifc", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".nff", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".smd", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".vta", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl2", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl3", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".pk3", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".mdmdcl2", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".md5mesh", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".md5anim", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".md5camera ", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".q3o", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".q3s", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".raw", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".ac", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".stl", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".dxf", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".irrmesh", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".irr", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".off", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".dterxf", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".mdl", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".hmp", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".mesh", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".skeleton", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".material", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".ms3d", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".lwo", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".lws", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".lxo", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".csm", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".ply", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".cob", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".scn", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".fbx", ::dooms::asset::eAssetType::THREE_D_MODEL },
	{ ".assbin", ::dooms::asset::eAssetType::THREE_D_MODEL },

	//////////////////////////////////////////////////////////////////////////

	{ ".txt", ::dooms::asset::eAssetType::TEXT },
	{ ".ini", ::dooms::asset::eAssetType::TEXT },

	/////////////////////////////////////////////////////

	{ ".glsl", ::dooms::asset::eAssetType::SHADER },

	/////////////////////////////////////////////////////////

	{ ".jpg", ::dooms::asset::eAssetType::TEXTURE },
	{ ".jpeg", ::dooms::asset::eAssetType::TEXTURE },
	{ ".png", ::dooms::asset::eAssetType::TEXTURE },
	{ ".bmp", ::dooms::asset::eAssetType::TEXTURE },
	{ ".tga", ::dooms::asset::eAssetType::TEXTURE },
	//{ ".hdr", ::dooms::asset::eAssetType::TEXTURE },
	{ ".dds", ::dooms::asset::eAssetType::TEXTURE }
};

const std::unordered_map<::dooms::asset::eAssetType, std::string>  dooms::assetImporter::AssetInBuildExtension
{
	{::dooms::asset::eAssetType::TEXTURE, ".dds"},
	{::dooms::asset::eAssetType::THREE_D_MODEL, ".assbin"}

};

std::optional<::dooms::asset::eAssetType>  dooms::assetImporter::GetAssetType(const std::filesystem::path& path)
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

bool dooms::assetImporter::ImportAssetJob(std::filesystem::path path, dooms::asset::Asset* const asset)
{
	const dooms::asset::eAssetType assetType = asset->GetEAssetType();

	dooms::assetImporter::AssetImporterWorker* const importerWorker = 
		dooms::assetImporter::AssetImporterWorkerManager::GetSingleton()->DequeueWorker(assetType);

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
		asset->SetAssetStatus(::dooms::asset::Asset::AssetStatus::CompletlyImported);
		dooms::ui::PrintText("Import Success : %s", path.string().c_str());
	}
	else
	{
		asset->SetAssetStatus(::dooms::asset::Asset::AssetStatus::FailToImport);
	}

	dooms::assetImporter::AssetImporterWorkerManager::GetSingleton()->EnqueueWorker(importerWorker);

	return isSuccess;

}

std::future<bool> dooms::assetImporter::PushImportingAssetJobToThreadPool
(
	std::filesystem::path path,
	dooms::asset::Asset* const asset
)
{
	std::function<bool()> newTask = std::bind(ImportAssetJob, std::move(path), asset);
	asset->SetAssetStatus(::dooms::asset::Asset::AssetStatus::WaitingImport);

	return dooms::resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(std::move(newTask));
}

std::vector<std::future<bool>> dooms::assetImporter::PushImportingAssetJobToThreadPool
(
	const std::vector<std::filesystem::path>& paths, 
	const std::vector<dooms::asset::Asset*>& assets
)
{
	D_ASSERT(paths.size() == assets.size());

	std::vector<std::function<bool()>> newTasks{};
	newTasks.reserve(paths.size());
	for (UINT32 i = 0; i < paths.size(); i++)
	{
		newTasks.push_back(std::bind(ImportAssetJob, std::move(paths[i]), assets[i]));
		assets[i]->SetAssetStatus(::dooms::asset::Asset::AssetStatus::WaitingImport);
	}

	/// <summary>
			/// maybe will be copied
			/// </summary>
			/// <param name="paths"></param>
			/// <returns></returns>
	return resource::JobSystem::GetSingleton()->PushBackJobChunkToPriorityQueue(std::move(newTasks));
}

