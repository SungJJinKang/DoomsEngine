#include "AssetImporter.h"
#include "../../Core.h"

#include "AssetImporterWorker.h"

using namespace Doom;
using namespace AssetImporter;




Assetimporter::Assetimporter(size_t poolSize)
{
	if (!threadPool)
	{
		InitializeThreadPool(poolSize);
	}
	else
	{
		DEBUG_LOG("AssetImporter Thread Pool is already initialized");
	}
}


Assetimporter::~Assetimporter()
{
	if (threadPool)
	{
		DEBUG_LOG("Deleting Importer Thread Pool");
		Assetimporter::threadPool.release();
		DEBUG_LOG("Complete Delete Importer Thread Pool");
	}

	//TODO : Release all apiimporter instance
}

void Assetimporter::InitializeThreadPool(size_t poolSize)
{
	DEBUG_LOG({ "Create Asset Importer Thread Pool", std::to_string(poolSize) });
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

std::optional<Doom::Asset::AssetType> Doom::AssetImporter::GetAssetType(const std::filesystem::path& path)
{
	if (path.has_extension())
	{
		auto extension = path.extension().string();
		try
		{
			return AssetExtension.at(extension.substr(1, extension.length() - 1));

		}
		catch (...)
		{
			return {};
		}
	}
	return {};
}