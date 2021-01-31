#include "AssetImporter.h"

using namespace doom;
using namespace assetimporter;

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

std::optional<doom::Asset::eAssetType> doom::assetimporter::GetAssetType(const std::filesystem::path& path)
{

	if (path.has_extension())
	{
		auto citer = AssetExtension.find(path.extension().string());
		if(citer != AssetExtension.cend())
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