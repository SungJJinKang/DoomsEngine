#pragma once

#include <string>
#include <filesystem>
#include <optional>
#include <future>

#include "../Core.h"
#include "../API/UUID.h"

#include "eAssetType.h"
#include "AssetMetaData.h"
#include "ZeroResetMoveContainer.h"

namespace doom
{
	

	class AudioAsset;
	class FontAsset;
	class TextAsset;
	class TextureAsset;
	class ThreeDModelAsset;




	namespace assetimporter
	{
		class AssetManager;
		class Assetimporter;
		template <::doom::asset::eAssetType assetType >
		class AssetImporterWorker;

		template <::doom::asset::eAssetType assetType >
		class ImportedAssetPort;

		template<::doom::asset::eAssetType assetType>
		class AssetContainer;

		template<::doom::asset::eAssetType loopVariable>
		struct OnEndImportInMainThreadFunctor;

	
	}

	namespace asset
	{

		class Asset
		{
			friend class ::doom::assetimporter::AssetManager;
			friend class ::doom::assetimporter::Assetimporter;

			template <eAssetType assetType>
			friend class ::doom::assetimporter::AssetImporterWorker;

			template <eAssetType assetType>
			friend class ::doom::assetimporter::ImportedAssetPort;

			template<eAssetType loopVariable>
			friend struct ::doom::assetimporter::OnEndImportInMainThreadFunctor;

			template<eAssetType loopVariable>
			friend class ::doom::assetimporter::AssetContainer;

		public:

			template <eAssetType assetType>
			struct asset_type
			{
				using type = void;
			};

			template <eAssetType assetType>
			using asset_type_t = typename asset_type<assetType>::type;

			template <eAssetType assetType>
			using imported_asset_future_t = typename std::future<std::optional<Asset::asset_type_t<assetType>>>;

			enum AssetStatus
			{
				FailToImport,

				/// <summary>
				/// Only Meta Data is imported
				/// </summary>
				NotImported,

				/// <summary>
				/// Be being imported
				/// </summary>
				WaitingImport,

				/// <summary>
				/// All data is imported
				/// </summary>
				CompletlyImported
			};

		private:

			AssetMetaData mAssetMetaData{};
			void SetBaseMetaData(const std::filesystem::path& path, const D_UUID& uuid);

		protected:

			AssetStatus mAssetStatus{ AssetStatus::NotImported };

			bool IsCalledEndImportInMainThread{ false };
			/// <summary>
			/// post processing after asset imported.
			/// this function should be called at main thread
			/// </summary>
			//void OnEndImportInMainThread_Internal();
			virtual void OnEndImportInMainThread_Internal() {}
			void OnEndImportInMainThread();
			virtual void OnEndImportInSubThread() {};

		public:

			Asset();
			Asset(const Asset&) = delete;
			Asset(Asset&&) noexcept = default;
			Asset& operator=(const Asset&) = delete;
			Asset& operator=(Asset&&) noexcept = default;
			virtual ~Asset() {}

			D_UUID GetUUID();
			const D_UUID& GetUUID() const;
			std::string GetAssetFileName();
			const std::string& GetAssetFileName() const;
			unsigned long long GetAssetFileSize() const;
			std::filesystem::path GetAssetPath();
			const std::filesystem::path& GetAssetPath() const;
			AssetStatus GetAssetStatus();

		};
	}

	
}


