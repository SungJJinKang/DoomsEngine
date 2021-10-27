#include "AssetImporterWorker_Texture.h"

#include <DirectXTex.h>
#include <Asset/TextureAsset.h>


bool doom::assetImporter::AssetImporterWorker_Texture::ImportTextureAsset(
	const std::filesystem::path& path,
	doom::asset::TextureAsset* textureAsset
)
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
			D_DEBUG_LOG("Fail To Load Texture", eLogType::D_ERROR);
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
			D_DEBUG_LOG("Cant Find Format", eLogType::D_ERROR);
			NEVER_HAPPEN;
			return false;
		}

		// TODO : �ѹ� ���� �� �ᵵ �ȴ� ���߿� ����
		const DirectX::Image* sourceImage = sourceScratchImage->GetImage(0, 0, 0); //mip map 0 image
		D_ASSERT(sourceImage->width % 4 == 0 && sourceImage->height % 4 == 0);

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
				D_DEBUG_LOG("Fail To Resize Texture", eLogType::D_ERROR);
				return false;
			}
		}


		auto mipmapedImage = std::make_unique<DirectX::ScratchImage>();
		hr = GenerateMipMaps(*(resizedImage->GetImage(0, 0, 0)), DirectX::TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT, MIP_MAP_LEVELS, *mipmapedImage, false);
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To Save DDS Texture", eLogType::D_ERROR);
			return false;
		}

		hr = Compress(mipmapedImage->GetImages(), mipmapedImage->GetImageCount(), mipmapedImage->GetMetadata(), compressTargetFormat, DirectX::TEX_COMPRESS_FLAGS::TEX_COMPRESS_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, *(ResultCompressedImage));
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To Compress Texture", eLogType::D_ERROR);
			return false;
		}


		// 		img.rowPitch = /*<number of bytes in a scanline of the source data>*/;
		// 		img.slicePitch = /*<number of bytes in the entire 2D image>*/;

		std::filesystem::path destinationPath = path;
		destinationPath.replace_extension(".dds");

		hr = SaveToDDSFile(ResultCompressedImage->GetImages(), ResultCompressedImage->GetImageCount(), ResultCompressedImage->GetMetadata(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, destinationPath.generic_wstring().c_str());
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To Save DDS Texture", eLogType::D_ERROR);
			return false;
		}
		else
		{
			D_DEBUG_LOG({ "Success To Save DDS Texture : ", destinationPath.string() }, eLogType::D_LOG);
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
			D_DEBUG_LOG("Fail To Load DDS Texture", eLogType::D_ERROR);
			return false;
		}

	}

	textureAsset->SetScratchImage(std::move(ResultCompressedImage));
	return true;
}

doom::assetImporter::AssetImporterWorker_Texture::AssetImporterWorker_Texture()
{
	if(AssetImporterWorker::IsInitialized == false)
	{
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To CoInitializeEx", eLogType::D_ERROR);
			NEVER_HAPPEN;
		}

		AssetImporterWorker::IsInitialized = true;
	}
	
}

doom::assetImporter::AssetImporterWorker_Texture::AssetImporterWorker_Texture(const AssetImporterWorker_Texture&) = default;
doom::assetImporter::AssetImporterWorker_Texture::AssetImporterWorker_Texture(AssetImporterWorker_Texture&&) noexcept = default;
doom::assetImporter::AssetImporterWorker_Texture& doom::assetImporter::AssetImporterWorker_Texture::operator=(const AssetImporterWorker_Texture&) = default;
doom::assetImporter::AssetImporterWorker_Texture& doom::assetImporter::AssetImporterWorker_Texture::operator=(AssetImporterWorker_Texture&&) noexcept = default;

bool doom::assetImporter::AssetImporterWorker_Texture::ImportSpecificAsset
(
	const std::filesystem::path& pathses,
	doom::asset::Asset* asset
)
{
	return ImportTextureAsset(pathses, static_cast<doom::asset::TextureAsset*>(asset));
}

doom::asset::eAssetType doom::assetImporter::AssetImporterWorker_Texture::GetEAssetType() const
{
	return doom::asset::eAssetType::TEXTURE;
}
