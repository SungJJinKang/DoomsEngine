#pragma once

#include <string>
#include <filesystem>
#include <optional>
#include <future>

#include <Core.h>
#include "../API/UUID.h"

#include "eAssetType.h"
#include "AssetMetaData.h"

namespace doom
{
	

	class AudioAsset;
	class FontAsset;
	class TextAsset;
	class TextureAsset;
	class ThreeDModelAsset;




	namespace asset
	{

		class DOOM_API Asset : public DObject
		{

		public:
			
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

			AssetMetaData mAssetMetaData;
		

		protected:

			AssetStatus mAssetStatus{ AssetStatus::NotImported };

			bool IsCalledEndImportInMainThread{ false };
			/// <summary>
			/// post processing after asset imported.
			/// this function should be called at main thread
			/// </summary>
			//void OnEndImportInMainThread_Internal();
			virtual void OnEndImportInMainThread_Internal() {}

		public:

			Asset();
			Asset(const Asset&) = delete;
			Asset(Asset&&) noexcept;
			Asset& operator=(const Asset&) = delete;
			Asset& operator=(Asset&&) noexcept;
			virtual ~Asset();

		
			void OnEndImportInMainThread();
			virtual void OnEndImportInSubThread() {};


			doom::D_UUID GetUUID() const;
			std::string GetAssetFileName();
			const std::string& GetAssetFileName() const;
			UINT64 GetAssetFileSize() const;
			const std::filesystem::path& GetAssetPath() const;
			AssetStatus GetAssetStatus();
			void SetAssetStatus(const AssetStatus assetStatus);
			void SetBaseMetaData(const std::filesystem::path& path, const D_UUID& uuid);

			virtual doom::asset::eAssetType GetEAssetType() const = 0;
		};
	}

	
}


