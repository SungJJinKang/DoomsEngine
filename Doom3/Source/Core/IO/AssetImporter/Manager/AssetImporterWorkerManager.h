#pragma once

#include <Core.h>

#include <array>
#include <atomic>

#include <concurrentqueue/blockingconcurrentqueue.h>
#include <Asset/eAssetType.h>

#include "../AssetImporterWorker/AssetImporterWorker.h"


namespace dooms
{
	namespace assetImporter
	{
		class AssetImporterWorker;

		class AssetImporterWorkerManager : public dooms::DObject, public ISingleton<AssetImporterWorkerManager>
		{

			DOBJECT_CLASS_BODY(AssetImporterWorkerManager, dooms::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

		private:

			inline constexpr static UINT32 MAX_ASSETIMPORTER_WORKER_COUNT = 3;

			std::array<moodycamel::BlockingConcurrentQueue<dooms::assetImporter::AssetImporterWorker*>, dooms::asset::ENUM_ASSETTYPE_COUNT> mAssetApiImportersQueue;
			std::array<std::atomic<INT32>, dooms::asset::ENUM_ASSETTYPE_COUNT> mAssetApiImportersCount{ 0, 0, 0, 0, 0, 0 };
			
			NO_DISCARD dooms::assetImporter::AssetImporterWorker* CreateAssetImporterWorker(const dooms::asset::eAssetType eAssetType);

			void InitializeAssetImporterWorkersStatic();
			void UnInitializeAssetImporterWorkersStatic();
			
		public:
		
			AssetImporterWorkerManager();
			~AssetImporterWorkerManager();
			AssetImporterWorkerManager(AssetImporterWorkerManager&&) noexcept = delete;
			AssetImporterWorkerManager& operator=(AssetImporterWorkerManager&&) noexcept = delete;
			AssetImporterWorkerManager(const AssetImporterWorkerManager&) = delete;
			AssetImporterWorkerManager& operator=(const AssetImporterWorkerManager&) = delete;
		
			void EnqueueWorker(dooms::assetImporter::AssetImporterWorker* const assetImporterWorker);
			dooms::assetImporter::AssetImporterWorker* DequeueWorker(const dooms::asset::eAssetType eAssetType);

			void ClearAssetImporterWorker();
			


		};
	}
}
