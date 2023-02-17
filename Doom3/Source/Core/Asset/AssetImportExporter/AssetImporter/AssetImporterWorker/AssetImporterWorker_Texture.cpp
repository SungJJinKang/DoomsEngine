#include "AssetImporterWorker_Texture.h"

#include <DirectXTex.h>
#include <Asset/TextureAsset.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>


bool dooms::assetImporter::AssetImporterWorker_Texture::ImportTextureAsset(
	const std::filesystem::path& path,
	dooms::asset::TextureAsset* textureAsset
)
{
	D_ASSERT_LOG(AssetImporterWorker::IsInitialized == true, "COM Library is not initilized");

	if(AssetImporterWorker::IsInitialized == true)
	{
		HRESULT hr;
		auto ResultCompressedImage = std::make_unique<DirectX::ScratchImage>();

		std::string sourceExtention = path.extension().generic_u8string();
		if (sourceExtention == ".bmp" || sourceExtention == ".png" || sourceExtention == ".tiff" ||
			sourceExtention == ".jpeg" || sourceExtention == ".jpg")
		{
			//IF file is not DDS file, import file and postprocess and export to DDS file

			std::wstring sourcepathUTF8 = path.generic_wstring();


			auto sourceScratchImage = std::make_unique<DirectX::ScratchImage>();

			hr = LoadFromWICFile(sourcepathUTF8.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, nullptr, *sourceScratchImage);
			if (FAILED(hr))
			{
				D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Load Texture");
				return false;
			}

			if (sourceScratchImage->GetImageCount() == 0)
			{
				D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Load Texture");
				return false;
			}

			DXGI_FORMAT compressTargetFormat{};
			switch (sourceScratchImage->GetMetadata().format)
			{
			case DXGI_FORMAT::DXGI_FORMAT_R8_UNORM:
				compressTargetFormat = DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM;
				break;

			case DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM:
				compressTargetFormat = DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM;
				break;

			case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM:
				compressTargetFormat = DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM;
				break;

				//TODO : CHECK 24 BIT texture And USE DXGI_FORMAT_BC1_UNORM
				// ����� 24��Ʈ RGB �̹����� Compress �� RGBA�� �ٲ�� �ִ�.
				//case DXGI_FORMAT::DXGI_FORMAT_r_UNORM:
				//	compressTargetFormat = DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM;
				//	break;

			default:
				D_DEBUG_LOG(eLogType::D_ERROR, "Cant Find Format");
				ASSUME_ZERO;
				return false;
			}
			
			const DirectX::Image* sourceImage = sourceScratchImage->GetImages();
			//D_ASSERT(sourceImage->width % 4 == 0 && sourceImage->height % 4 == 0);
				

			auto resizedImage = std::make_unique<DirectX::ScratchImage>();

			size_t maxSize = max(sourceImage->width, sourceImage->height);
			size_t resizeRatio = maxSize > MAX_IMAGE_SIZE
				? maxSize / MAX_IMAGE_SIZE : 1;

			if (resizeRatio == 1)
			{
				//we don't need resize
				resizedImage = std::move(sourceScratchImage);
			}
			else
			{
				hr = Resize(*sourceImage, sourceScratchImage->GetMetadata().width / resizeRatio, sourceScratchImage->GetMetadata().height / resizeRatio, DirectX::TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT, *resizedImage);
				if (FAILED(hr))
				{
					D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Resize Texture");
					return false;
				}
			}


			auto mipmapedImage = std::make_unique<DirectX::ScratchImage>();
			hr = GenerateMipMaps(*(resizedImage->GetImage(0, 0, 0)), DirectX::TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT, MIP_MAP_LEVELS, *mipmapedImage, false);
			if (FAILED(hr))
			{
				D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Save DDS Texture");
				return false;
			}

			hr = Compress(mipmapedImage->GetImages(), mipmapedImage->GetImageCount(), mipmapedImage->GetMetadata(), compressTargetFormat, DirectX::TEX_COMPRESS_FLAGS::TEX_COMPRESS_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, *(ResultCompressedImage));
			if (FAILED(hr))
			{
				D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Compress Texture");
				return false;
			}


			// 		img.rowPitch = /*<number of bytes in a scanline of the source data>*/;
			// 		img.slicePitch = /*<number of bytes in the entire 2D image>*/;

			std::filesystem::path destinationPath = path;
			destinationPath.replace_extension(".dds");

			hr = SaveToDDSFile(ResultCompressedImage->GetImages(), ResultCompressedImage->GetImageCount(), ResultCompressedImage->GetMetadata(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, destinationPath.generic_wstring().c_str());
			if (FAILED(hr))
			{
				D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Save DDS Texture");
				return false;
			}
			else
			{
				D_DEBUG_LOG(eLogType::D_LOG, "Success To Save DDS Texture : %s", destinationPath.string().c_str());
				return false;
			}

		}
		else if (sourceExtention == ".dds")
		{	//already compressed, just send to gpu. 
			//you don't need decompress if you use DXT
			DirectX::TexMetadata info;
			hr = LoadFromDDSFile(path.generic_wstring().c_str(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, &info, *ResultCompressedImage);
			
			if (FAILED(hr))
			{
				D_DEBUG_LOG(eLogType::D_ERROR, "Fail To Load DDS Texture");
				return false;
			}

		}

		textureAsset->SetScratchImage(std::move(ResultCompressedImage), graphics::GraphicsAPI::eBindFlag::BIND_SHADER_RESOURCE);
		return true;
	}
	else
	{
		return false;
	}	
}

dooms::assetImporter::AssetImporterWorker_Texture::AssetImporterWorker_Texture()
{
	if(AssetImporterWorker::IsInitialized == false)
	{
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		D_ASSERT_LOG(FAILED(hr) == false, "Fail to initalize COM Library"); // https://m.blog.naver.com/milennium9/220065501067
		if (FAILED(hr))
		{
			D_DEBUG_LOG(eLogType::D_ERROR, "Fail To CoInitializeEx");
			ASSUME_ZERO;
		}

		AssetImporterWorker::IsInitialized = true;
	}
	
}

dooms::assetImporter::AssetImporterWorker_Texture::~AssetImporterWorker_Texture()
{
}

dooms::assetImporter::AssetImporterWorker_Texture::AssetImporterWorker_Texture(const AssetImporterWorker_Texture&) = default;
dooms::assetImporter::AssetImporterWorker_Texture::AssetImporterWorker_Texture(AssetImporterWorker_Texture&&) noexcept = default;
dooms::assetImporter::AssetImporterWorker_Texture& dooms::assetImporter::AssetImporterWorker_Texture::operator=(const AssetImporterWorker_Texture&) = default;
dooms::assetImporter::AssetImporterWorker_Texture& dooms::assetImporter::AssetImporterWorker_Texture::operator=(AssetImporterWorker_Texture&&) noexcept = default;

bool dooms::assetImporter::AssetImporterWorker_Texture::ImportSpecificAsset
(
	const std::filesystem::path& pathses,
	dooms::asset::Asset* asset
)
{
	return ImportTextureAsset(pathses, static_cast<dooms::asset::TextureAsset*>(asset));
}

dooms::asset::eAssetType dooms::assetImporter::AssetImporterWorker_Texture::GetEAssetType() const
{
	return dooms::asset::eAssetType::TEXTURE;
}
