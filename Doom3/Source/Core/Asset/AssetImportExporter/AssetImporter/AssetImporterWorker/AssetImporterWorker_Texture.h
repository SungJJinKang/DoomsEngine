#pragma once

#include "AssetImporterWorker.h"

#include "AssetImporterWorker_Texture.reflection.h"
namespace dooms
{
	namespace asset
	{
		class TextureAsset;
	}
	
	namespace assetImporter
	{
		
		class DOOM_API D_CLASS AssetImporterWorker_Texture : public AssetImporterWorker
		{
			
			GENERATE_BODY()

			//static constexpr inline UINT32 AVAILIABLE_FORMAT_TYPE = CMP_FORMAT_DXT5 | CMP_FORMAT_DXT1 | CMP_FORMAT_BC5 | CMP_FORMAT_BC4;

			bool ImportTextureAsset(const std::filesystem::path& path, dooms::asset::TextureAsset* textureAsset);

		public:

			AssetImporterWorker_Texture();
			virtual ~AssetImporterWorker_Texture();
			AssetImporterWorker_Texture(const AssetImporterWorker_Texture&);
			AssetImporterWorker_Texture(AssetImporterWorker_Texture&&) noexcept;
			AssetImporterWorker_Texture& operator=(const AssetImporterWorker_Texture&);
			AssetImporterWorker_Texture& operator=(AssetImporterWorker_Texture&&) noexcept;

			static inline FLOAT32 TEXTURE_COMPRESSION_QUALITY{};
			static inline INT32 MIP_MAP_LEVELS{};
			static inline INT32 MAX_IMAGE_SIZE{};
			static inline bool bmIsInitialized{ false };

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic(){}
		};
		
	}
}