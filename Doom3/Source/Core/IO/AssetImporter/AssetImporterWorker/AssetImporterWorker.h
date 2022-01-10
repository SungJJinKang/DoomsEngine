#pragma once

#include <Core.h>

#include <filesystem>
#include <atomic>
#include <mutex>

#include <Asset/eAssetType.h>

#include "AssetImporterWorker.reflection.h"
namespace dooms
{
	namespace asset
	{
		class Asset;
	}

	namespace assetImporter
	{
		class DOOM_API D_CLASS AssetImporterWorker : public DObject
		{
			GENERATE_BODY()

		private:

			static std::mutex mMutex;

		protected:

			bool IsInitialized = false;
			static std::atomic<bool> IsInitializedStatic;

		public:

			AssetImporterWorker();
			AssetImporterWorker(const AssetImporterWorker&);
			AssetImporterWorker(AssetImporterWorker&&) noexcept;
			AssetImporterWorker& operator=(const AssetImporterWorker&);
			AssetImporterWorker& operator=(AssetImporterWorker&&) noexcept;
			virtual ~AssetImporterWorker();

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) = 0;
			virtual dooms::asset::eAssetType GetEAssetType() const = 0;

			FORCE_INLINE bool GetIsIsInitialized()
			{
				return IsInitialized;
			}
		};
	}
}