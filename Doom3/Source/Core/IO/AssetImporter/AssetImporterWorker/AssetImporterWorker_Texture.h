#pragma once

#include "AssetImporterWorker.h"


namespace doom
{
	namespace asset
	{
		class TextureAsset;
	}
	
	namespace assetimporter
	{
		
		class DOOM_API AssetImporterWorker_Texture : public AssetImporterWorker
		{
			//static constexpr inline unsigned int AVAILIABLE_FORMAT_TYPE = CMP_FORMAT_DXT5 | CMP_FORMAT_DXT1 | CMP_FORMAT_BC5 | CMP_FORMAT_BC4;

			bool ImportTextureAsset(const std::filesystem::path& path, doom::asset::TextureAsset* textureAsset);

		public:

			AssetImporterWorker_Texture();
			AssetImporterWorker_Texture(const AssetImporterWorker_Texture&);
			AssetImporterWorker_Texture(AssetImporterWorker_Texture&&) noexcept;
			AssetImporterWorker_Texture& operator=(const AssetImporterWorker_Texture&);
			AssetImporterWorker_Texture& operator=(AssetImporterWorker_Texture&&) noexcept;

			static inline float TEXTURE_COMPRESSION_QUALITY{};
			static inline int MIP_MAP_LEVELS{};
			static inline int MAX_IMAGE_SIZE{};
			static inline bool bmIsInitialized{ false };

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, doom::asset::Asset* asset) override;

			virtual doom::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic(){}
		};
		
	}
}