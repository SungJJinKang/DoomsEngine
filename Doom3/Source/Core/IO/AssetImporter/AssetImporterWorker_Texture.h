#pragma once


#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include <utility>
#include <type_traits>

#include "../../Asset/TextureAsset.h"
#include "../../API/STB_IMAGE.h"

namespace doom
{
	namespace assetimporter
	{
		//static_assert(std::is_same_v<ai_real, float>); // ai_real is type of assimp vector's element, So we check if it is float type

		template <>
		class AssetImporterWorker<eAssetType::TEXTURE>
		{
			friend class Assetimporter;
		private:
			static std::optional <Asset::asset_type_t<eAssetType::TEXTURE>> ImportSpecificAsset(const std::filesystem::path& path)
			{
					stbi_set_flip_vertically_on_load(true);

				    int width,height,componentCount;
					unsigned char *data = stbi_load(path.u8string().c_str(), &width, &height, &componentCount, 0);
					unsigned char *dxtData{NULL};

					TextureAsset::eTextureCompressionType textureCompressionType{ TextureAsset::eTextureCompressionType::NONE };

					constexpr unsigned int pixelCountOfBlock = 4 * 4;
					constexpr unsigned int pixelSize = 4;

					if (width % 4 == 0 && height % 4 == 0)
					{
						
						if (componentCount == 1)
						{
							stb_compress_bc4_block(dxtData, data);
							textureCompressionType = TextureAsset::eTextureCompressionType::BC4;
						}
						else if (componentCount == 2)
						{
							stb_compress_bc5_block(dxtData, data);
							textureCompressionType = TextureAsset::eTextureCompressionType::BC5;
						}
						else if (componentCount == 4)
						{
							unsigned char sourceTemp[pixelCountOfBlock * pixelSize]; // each fixel has 4 byte data
							unsigned char destinationTemp[pixelCountOfBlock * pixelSize / 8]; // EXT compression is 8 : 1 compression
							dxtData = new unsigned char[width * height * pixelSize / 8]; // EXT compression is 8 : 1 compression
							for (int j = 0; j < height; j += 4)
							{//y
								for (int i = 0; i < width; i += 4)
								{//x
									unsigned int targetIndex = j * width * 4 * 4 + i * 16;

									std::memmove(&sourceTemp[pixelSize * 4 * 0], &data[targetIndex], 16);
									std::memmove(&sourceTemp[pixelSize * 4 * 1], &data[targetIndex + 16], 16);
									std::memmove(&sourceTemp[pixelSize * 4 * 2], &data[targetIndex + 16 * 2], 16);
									std::memmove(&sourceTemp[pixelSize * 4 * 3], &data[targetIndex + 16 * 3], 16);

									stb_compress_dxt_block(destinationTemp, sourceTemp, 1, STB_DXT_NORMAL);


								}
							}

							
							textureCompressionType = TextureAsset::eTextureCompressionType::DXT;
						}
					}
					
				
					TextureAsset textureAsset{ width, height, componentCount, dxtData, textureCompressionType };
					//stbi_image_free(data);

					// ... process data if not NULL ...
					// ... x = width, y = height, n = # 8-bit components per pixel ...
					// ... replace '0' with '1'..'4' to force that many components per pixel
					// ... but 'n' will always be the number that it would have been if you said 0
					
					if (dxtData != NULL)
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