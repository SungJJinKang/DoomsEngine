#pragma once

#include <string>
#include <filesystem>
#include <optional>
#include <future>

#include <Core.h>
#include "../API/UUID.h"

#include "eAssetType.h"
#include "AssetMetaData.h"


#include "Asset.reflection.h"
namespace dooms
{
	
	namespace asset
	{
		class AudioAsset;
		class FontAsset;
		class TextAsset;
		class TextureAsset;
		class ThreeDModelAsset;
	}


	D_NAMESPACE(dooms::asset)
	namespace asset
	{

		class DOOM_API D_CLASS Asset : public DObject
		{
			GENERATE_BODY()
			
			

		public:
			
			enum D_ENUM AssetStatus
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

			virtual void OnSetPendingKill() override;
		
			void OnEndImportInMainThread();
			virtual void OnEndImportInSubThread() {};


			dooms::D_UUID GetUUID() const;
			/**
			 * \brief 
			 * \return Returned extension string has ".". ex) ".bmp", ".png"
			 */
			std::string GetAssetExtension() const;
			std::string GetAssetFileName();
			const std::string& GetAssetFileName() const;
			UINT64 GetAssetFileSize() const;
			std::string GetAssetPathAsStr() const;
			std::string GetAssetPathAsUTF8Str() const;
			std::wstring GetAssetPathAsWideStr() const;
			const std::filesystem::path& GetAssetPath() const;
			AssetStatus GetAssetStatus();
			void SetAssetStatus(const AssetStatus assetStatus);
			void SetBaseMetaData(const std::filesystem::path& path, const D_UUID& uuid);

			virtual dooms::asset::eAssetType GetEAssetType() const = 0;
		};
	}

	
}


