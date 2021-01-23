#pragma once
#include <optional>

#include "../../Core.h"

#include "../../Asset/Asset.h"
#include "../../../Helper/ThreadPool_Cpp/ThreadPool.h"


#ifdef DEBUG_MODE
#define THREADPOOL_DEBUG
#endif



namespace Doom
{
	namespace AssetImporter
	{
		template <Asset::AssetType assetType>
		std::optional<Asset::asset_type_t<assetType>> ReadAssetFile(std::filesystem::path path);

		/*
		template <Asset::AssetType assetType>
		void Doom::AssetImporterWorker<assetType>::AddApiImporter()
		{
			for (size_t i = 0; i < Assetimporter::GetThreadPool()->PoolSize; i++)
			{
				std::unique_ptr<ApiImporterType> apiImporter = std::make_unique<ApiImporterType>();
				this->InitApiImporter(*apiImporter);

				ImporterQueue.push(std::move(apiImporter));
			}
		}
		*/

	}
}