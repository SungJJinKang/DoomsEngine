#include "AssetImporterWorker_Texture.h"

#include <DirectXTex.h>

using namespace doom;
using namespace doom::assetimporter;
using namespace DirectX;

template class doom::assetimporter::AssetImporterWorker<eAssetType::TEXTURE>;

std::optional <Asset::asset_type_t<eAssetType::TEXTURE>> doom::assetimporter::AssetImporterWorker<eAssetType::TEXTURE>::ImportSpecificAsset(const std::filesystem::path& path)
{
	//CreateiM
	if (doom::assetimporter::AssetImporterWorker<eAssetType::TEXTURE>::bmIsInitialized == false)
	{
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To CoInitializeEx", eLogType::D_ERROR);
			return {};
		}
		doom::assetimporter::AssetImporterWorker<eAssetType::TEXTURE>::bmIsInitialized = true;
		
	}

	HRESULT hr;
	auto ResultCompressedImage = std::make_unique<ScratchImage>();

	auto sourceExtention = path.extension().string();
	if (sourceExtention == ".bmp" || sourceExtention == ".png" || sourceExtention == ".tiff" ||
		sourceExtention == ".jpeg" || sourceExtention == ".jpg")
	{
		auto sourcepathCstr = path.c_str();

	
		auto sourceScratchImage = std::make_unique<ScratchImage>();
		hr = LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, *sourceScratchImage);
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To Load Texture", eLogType::D_ERROR);
			return {};
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
			// 현재는 24비트 RGB 이미지도 Compress 후 RGBA로 바뀌고 있다.
		//case DXGI_FORMAT::DXGI_FORMAT_r_UNORM:
		//	compressTargetFormat = DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM;
		//	break;

		default:
			D_DEBUG_LOG("Cant Find Format", eLogType::D_ERROR);
			NODEFAULT;
		}

		// TODO : 한번 쓰건 또 써도 된다 나중에 수정
		const DirectX::Image* sourceImage = sourceScratchImage->GetImage(0, 0, 0); //mip map 0 image
		D_ASSERT(sourceImage->width % 4 == 0 && sourceImage->height % 4 == 0);

		auto resizedImage = std::make_unique<ScratchImage>();

		size_t maxSize = max(sourceImage->width, sourceImage->height);
		size_t resizeRatio = maxSize > AssetImporterWorker<eAssetType::TEXTURE>::MAX_IMAGE_SIZE
		? maxSize / AssetImporterWorker<eAssetType::TEXTURE>::MAX_IMAGE_SIZE : 1;
		
		if (resizeRatio == 1)
		{
			//we don't need resize
			resizedImage = std::move(sourceScratchImage);
		}
		else
		{
			hr = Resize(*sourceImage, sourceScratchImage->GetMetadata().width / resizeRatio, sourceScratchImage->GetMetadata().height / resizeRatio, TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT, *resizedImage);
			if (FAILED(hr))
			{
				D_DEBUG_LOG("Fail To Resize Texture", eLogType::D_ERROR);
				return {};
			}
		}
		
	
		auto mipmapedImage = std::make_unique<ScratchImage>();
		hr = GenerateMipMaps(*(resizedImage->GetImage(0, 0, 0)), TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT, AssetImporterWorker<eAssetType::TEXTURE>::MIP_MAP_LEVELS, *mipmapedImage, false);
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To Save DDS Texture", eLogType::D_ERROR);
			return {};
		}

		hr = Compress(mipmapedImage->GetImages(), mipmapedImage->GetImageCount(), mipmapedImage->GetMetadata(), compressTargetFormat, TEX_COMPRESS_FLAGS::TEX_COMPRESS_DEFAULT, TEX_THRESHOLD_DEFAULT, *(ResultCompressedImage));
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To Compress Texture", eLogType::D_ERROR);
			return {};
		}
		

// 		img.rowPitch = /*<number of bytes in a scanline of the source data>*/;
// 		img.slicePitch = /*<number of bytes in the entire 2D image>*/;

		auto destinationPath = path;
		destinationPath.replace_extension(".dds");

		hr = SaveToDDSFile(*(ResultCompressedImage->GetImages()), DDS_FLAGS::DDS_FLAGS_NONE, destinationPath.c_str());
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To Save DDS Texture", eLogType::D_ERROR);
			return {};
		}

	}
	else if (sourceExtention == ".dds")
	{	//already compressed, just send to gpu. 
		//you don't need decompress if you use DXT
		TexMetadata info;
		hr = LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, &info,*ResultCompressedImage);
		if (FAILED(hr))
		{
			D_DEBUG_LOG("Fail To Load DDS Texture", eLogType::D_ERROR);
			return {};
		}

	}
	auto ResultCompressedImagePointer = ResultCompressedImage.get();
	ResultCompressedImage.release(); // not destroy Object, just set null pointer to unique_ptr
	return ResultCompressedImagePointer;
}