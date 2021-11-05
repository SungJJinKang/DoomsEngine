#pragma once

#include <Core.h>

#include <array>
#include <atomic>

#include <concurrentqueue/blockingconcurrentqueue.h>
#include <Asset/eAssetType.h>

#include "../AssetImporterWorker/AssetImporterWorker.h"


namespace doom
{
	namespace assetImporter
	{
		class AssetImporterWorker;

		class AssetImporterWorkerManager : public doom::DObject, public ISingleton<AssetImporterWorkerManager>
		{

			DOBJECT_CLASS_BODY(AssetImporterWorkerManager, doom::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

		private:

			inline constexpr static UINT32 MAX_ASSETIMPORTER_WORKER_COUNT = 3;

			std::array<moodycamel::BlockingConcurrentQueue<doom::assetImporter::AssetImporterWorker*>, doom::asset::ENUM_ASSETTYPE_COUNT> mAssetApiImportersQueue;
			std::array<std::atomic<INT32>, doom::asset::ENUM_ASSETTYPE_COUNT> mAssetApiImportersCount{ 0, 0, 0, 0, 0, 0 };
			
			NO_DISCARD doom::assetImporter::AssetImporterWorker* CreateAssetImporterWorker(const doom::asset::eAssetType eAssetType);

			void InitializeAssetImporterWorkersStatic();
			
		public:
		
			AssetImporterWorkerManager();
			~AssetImporterWorkerManager();
			AssetImporterWorkerManager(AssetImporterWorkerManager&&) noexcept = delete;
			AssetImporterWorkerManager& operator=(AssetImporterWorkerManager&&) noexcept = delete;
			AssetImporterWorkerManager(const AssetImporterWorkerManager&) = delete;
			AssetImporterWorkerManager& operator=(const AssetImporterWorkerManager&) = delete;
		
			void EnqueueWorker(doom::assetImporter::AssetImporterWorker* const assetImporterWorker);
			doom::assetImporter::AssetImporterWorker* DequeueWorker(const doom::asset::eAssetType eAssetType);

			void ClearAssetImporterWorker();
			


		};
	}
}
