#pragma once


#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include <utility>

#include <optional>

#include "../../Asset/TextureAsset.h"


namespace doom
{
	class GameCore;
	namespace assetimporter
	{

		template <>
		void InitAssetImport<eAssetType::TEXTURE>();
		template <>
		void EndAssetImport<eAssetType::TEXTURE>();

		template <>
		class AssetImporterWorker<eAssetType::TEXTURE>
		{
			//static constexpr inline unsigned int AVAILIABLE_FORMAT_TYPE = CMP_FORMAT_DXT5 | CMP_FORMAT_DXT1 | CMP_FORMAT_BC5 | CMP_FORMAT_BC4;

			friend class GameCore;
			friend class Assetimporter;
		private:

			static inline float TEXTURE_COMPRESSION_QUALITY{};
			static inline int MIP_MAP_LEVELS{};
			static inline int MAX_IMAGE_SIZE{};
			static inline bool bmIsInitialized{ false };

			static std::optional <Asset::asset_type_t<eAssetType::TEXTURE>> ImportSpecificAsset(const std::filesystem::path& path);
			//static bool CompressTexture(const std::filesystem::path& path, CMP_MipSet& sourceTexture, CMP_MipSet& resultTexture);
			//static void SaveTexture(const std::filesystem::path& path, CMP_MipSet& texture, bool freeTexture);

			
		};

		extern template class AssetImporterWorker<eAssetType::TEXTURE>;
	}
}