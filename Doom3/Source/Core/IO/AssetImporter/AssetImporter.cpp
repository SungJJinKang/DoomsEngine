#include "AssetImporter.h"

using namespace doom;
using namespace assetimporter;


const std::map<std::string, doom::Asset::eAssetType> doom::assetimporter::Assetimporter::AssetExtension
{
	//3D Model Asset Formats
	{".dae", doom::Asset::eAssetType::THREE_D_MODEL},
	{ ".blend", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".bvh", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".3ds", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".ase", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".obj", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".glFT", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".ply", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".dxf", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".ifc", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".nff", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".smd", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".vta", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".mdl", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".mdl2", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".mdl3", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".pk3", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".mdmdcl2", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".md5mesh", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".md5anim", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".md5camera ", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".q3o", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".q3s", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".raw", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".ac", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".stl", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".dxf", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".irrmesh", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".irr", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".off", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".dterxf", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".mdl", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".hmp", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".mesh", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".skeleton", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".material", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".ms3d", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".lwo", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".lws", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".lxo", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".csm", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".ply", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".cob", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".scn", doom::Asset::eAssetType::THREE_D_MODEL },
	{ ".fbx", doom::Asset::eAssetType::THREE_D_MODEL },
	//////////////////////////////////////////////////////////////////////////

	{ ".txt", doom::Asset::eAssetType::TEXT },
	{ ".ini", doom::Asset::eAssetType::TEXT },

	/////////////////////////////////////////////////////

	{ ".glsl", doom::Asset::eAssetType::SHADER },

	/////////////////////////////////////////////////////////

	{ ".jpg", doom::Asset::eAssetType::TEXTURE },
	{ ".jpeg", doom::Asset::eAssetType::TEXTURE },
	{ ".png", doom::Asset::eAssetType::TEXTURE },
	{ ".bmp", doom::Asset::eAssetType::TEXTURE },
	{ ".psd", doom::Asset::eAssetType::TEXTURE },
	{ ".tga", doom::Asset::eAssetType::TEXTURE },
	{ ".hdr", doom::Asset::eAssetType::TEXTURE },
	{ ".pic", doom::Asset::eAssetType::TEXTURE },
	{ ".pnm", doom::Asset::eAssetType::TEXTURE }
};

std::optional<doom::Asset::eAssetType> Assetimporter::GetAssetType(const std::filesystem::path& path)
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

Assetimporter::Assetimporter(size_t poolSize)
{
	if (!threadPool)
	{
		InitializeThreadPool(poolSize);
	}
	else
	{
		D_DEBUG_LOG("AssetImporter Thread Pool is already initialized");
	}
}


Assetimporter::~Assetimporter()
{
	if (threadPool)
	{
		D_DEBUG_LOG("Deleting Importer Thread Pool");
		Assetimporter::threadPool.reset(nullptr); // reset(nullptr) will delete managed object of unique_ptr
		D_DEBUG_LOG("Complete Delete Importer Thread Pool");

		ClearAllApiImporterQueue();
	}

}

void Assetimporter::InitializeThreadPool(size_t poolSize)
{
	D_DEBUG_LOG({ "Create Asset Importer Thread Pool", std::to_string(poolSize) });
	Assetimporter::threadPool = std::make_unique<::ThreadPool>(poolSize);
}

const std::unique_ptr<ThreadPool>& Assetimporter::GetThreadPool()
{
	if (!threadPool)
	{
		InitializeThreadPool(1);
	}

	return threadPool;
}

bool Assetimporter::IsThreadPoolInitialized()
{
	return static_cast<bool>(threadPool);
}
