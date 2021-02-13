#pragma once


#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include <utility>
#include "../../Asset/TextureAsset.h"
#include "../../API/STB_IMAGE.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		class AssetImporterWorker<eAssetType::TEXTURE>
		{
			friend class Assetimporter;
		private:
			static std::optional <Asset::asset_type_t<eAssetType::TEXTURE>> ImportSpecificAsset(const std::filesystem::path& path)
			{
					stbi_set_flip_vertically_on_load(true);

				    int x,y,n;
					unsigned char *data = stbi_load(path.u8string().c_str(), &x, &y, &n, 0);

					TextureAsset textureAsset{ x, y, n, data };
					//stbi_image_free(data);

					// ... process data if not NULL ...
					// ... x = width, y = height, n = # 8-bit components per pixel ...
					// ... replace '0' with '1'..'4' to force that many components per pixel
					// ... but 'n' will always be the number that it would have been if you said 0
					
					if (data != NULL)
					{
						return std::move(textureAsset);
					}
					else
					{
						return {};
					}
			}
		};
	
	}
}