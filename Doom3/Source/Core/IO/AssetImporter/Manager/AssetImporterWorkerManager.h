#pragma once

#include <Core.h>

#include <array>
#include <memory>
#include <vector>

#include <concurrentqueue/blockingconcurrentqueue.h>
#include <Asset/eAssetType.h>

#include "../AssetImporterWorker/AssetImporterWorker.h"

namespace doom
{
	namespace assetimporter
	{
		class AssetImporterWorker;

		class AssetImporterWorkerManager : public doom::DObject, public ISingleton<AssetImporterWorkerManager>
		{

		private:

			std::array<moodycamel::BlockingConcurrentQueue<doom::assetimporter::AssetImporterWorker*>, doom::asset::ENUM_ASSETTYPE_COUNT> mAssetApiImportersQueue;
			std::array<std::vector<std::unique_ptr<doom::assetimporter::AssetImporterWorker>>, doom::asset::ENUM_ASSETTYPE_COUNT> mCreatedAssetApiImporters;

			[[nodiscard]] doom::assetimporter::AssetImporterWorker* CreateAssetImporterWorker(const doom::asset::eAssetType eAssetType);

		public:

			AssetImporterWorkerManager();
			~AssetImporterWorkerManager();
			AssetImporterWorkerManager(AssetImporterWorkerManager&&) noexcept;
			AssetImporterWorkerManager& operator=(AssetImporterWorkerManager&&) noexcept;
			AssetImporterWorkerManager(const AssetImporterWorkerManager&) = delete;
			AssetImporterWorkerManager& operator=(const AssetImporterWorkerManager&) = delete;
		
			void EnqueueWorker(doom::assetimporter::AssetImporterWorker* const assetImporterWorker);
			doom::assetimporter::AssetImporterWorker* DequeueWorker(const doom::asset::eAssetType eAssetType);

			void ClearAssetImporterWorker();
			


		};
	}
}
