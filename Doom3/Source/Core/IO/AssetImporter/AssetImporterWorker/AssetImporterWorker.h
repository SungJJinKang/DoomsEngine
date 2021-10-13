#pragma once

#include <Core.h>
#include <filesystem>

#include <Asset/eAssetType.h>

namespace doom
{
	namespace asset
	{
		class Asset;
	}

	namespace assetimporter
	{
		class DOOM_API AssetImporterWorker
		{
		protected:

			inline static bool IsInitialized = false;

		public:

			AssetImporterWorker();
			AssetImporterWorker(const AssetImporterWorker&);
			AssetImporterWorker(AssetImporterWorker&&) noexcept;
			AssetImporterWorker& operator=(const AssetImporterWorker&);
			AssetImporterWorker& operator=(AssetImporterWorker&&) noexcept;
			virtual ~AssetImporterWorker();

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, doom::asset::Asset* asset) = 0;
			virtual doom::asset::eAssetType GetEAssetType() const = 0;
		};
	}
}