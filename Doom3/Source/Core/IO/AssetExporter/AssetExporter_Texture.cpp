#include "AssetExporter_Texture.h"

#include <Graphics/Texture/Texture.h>
#include <DirectXTex.h>

#include <UI/PrintText.h>

namespace doom
{
	namespace assetExporter
	{
		namespace assetExporterTexture
		{
			DirectX::Image ConvertToDirectXImage
			(
				const INT32 lodLevel,
				UINT8* pixels,
				const SIZE_T width,
				const SIZE_T height,
				const doom::graphics::Texture::ePixelFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType
			)
			{
				int PixelChannelSize = 1;
				switch (dataType)
				{
				case doom::graphics::Texture::eDataType::UNSIGNED_BYTE:

					PixelChannelSize = 1;
					break;

				case doom::graphics::Texture::eDataType::FLOAT:

					PixelChannelSize = 4;
					break;

				default:

					NEVER_HAPPEN;
				}
				
				DirectX::Image dxImage;
				dxImage.width = width;
				dxImage.height = height;
				dxImage.pixels = pixels;

				switch (pixelFormat)
				{
				case doom::graphics::Texture::ePixelFormat::RED:
					dxImage.rowPitch = PixelChannelSize * 1 * dxImage.width;
					dxImage.slicePitch = PixelChannelSize * 1 * dxImage.width * dxImage.height;
					dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
					break;

				case doom::graphics::Texture::ePixelFormat::RG:
					dxImage.rowPitch = PixelChannelSize * 2 * dxImage.width;
					dxImage.slicePitch = PixelChannelSize * 2 * dxImage.width * dxImage.height;
					dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;
					break;

				case doom::graphics::Texture::ePixelFormat::RGB:
					dxImage.rowPitch = PixelChannelSize * 4 * dxImage.width;
					dxImage.slicePitch = PixelChannelSize * 4 * dxImage.width * dxImage.height;
					dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; // RGS also use DXGI_FORMAT_R8G8B8A8_UNORM
					break;

				case doom::graphics::Texture::ePixelFormat::RGBA:
					dxImage.rowPitch = PixelChannelSize * 4 * dxImage.width;
					dxImage.slicePitch = PixelChannelSize * 4 * dxImage.width * dxImage.height;
					dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
					break;

				default:
					NEVER_HAPPEN;
				}

				return dxImage;
			}


			DirectX::Image ConvertToDirectXImage
			(
				const doom::graphics::Texture* const exportedTexture,
				const INT32 lodLevel,
				const doom::graphics::Texture::ePixelFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType
			)
			{
				D_ASSERT(IsValid(exportedTexture) == true);
				
				return ConvertToDirectXImage(
					lodLevel,
					exportedTexture->GetTexturePixelsUnsafe(lodLevel),
					exportedTexture->GetTextureMetaDataINT32(lodLevel, graphics::Texture::eTextureMataDataType::TEXTURE_WIDTH),
					exportedTexture->GetTextureMetaDataINT32(lodLevel, graphics::Texture::eTextureMataDataType::TEXTURE_HEIGHT),
					pixelFormat,
					dataType
				);

			}
		}
	}
}


void doom::assetExporter::assetExporterTexture::ExportTextureAsDDS
(
	DirectX::Image dxImage, 
	const INT32 lodLevel,
	const doom::graphics::Texture::ePixelFormat pixelFormat, 
	const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath)
{
	std::unique_ptr<UINT8[]> pixels(dxImage.pixels); // for safety

	DXGI_FORMAT compressFormat;

	switch (pixelFormat)
	{
	case doom::graphics::Texture::ePixelFormat::RED:
		compressFormat = DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM;
		break;

	case doom::graphics::Texture::ePixelFormat::RG:
		compressFormat = DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM;
		break;

	case doom::graphics::Texture::ePixelFormat::RGB:
		compressFormat = DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM;
		break;

	case doom::graphics::Texture::ePixelFormat::RGBA:
		compressFormat = DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM;
		break;

	default:
		NEVER_HAPPEN;
	}

	HRESULT hr;

	DirectX::ScratchImage ResultCompressedImage;
	hr = DirectX::Compress(dxImage, compressFormat, DirectX::TEX_COMPRESS_FLAGS::TEX_COMPRESS_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, ResultCompressedImage);

	D_ASSERT(FAILED(hr) == false);
	if (FAILED(hr) == false)
	{
		std::filesystem::path destinationPath = exportPath;
		destinationPath.replace_extension(".dds");

		hr = DirectX::SaveToDDSFile(ResultCompressedImage.GetImages(), ResultCompressedImage.GetImageCount(), ResultCompressedImage.GetMetadata(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, destinationPath.generic_wstring().c_str());

		D_ASSERT(FAILED(hr) == false);
		if (FAILED(hr) == true)
		{
			doom::ui::PrintText("Fail To ExportTexture as DDS ( %s )", destinationPath.string().c_str());
		}
		else
		{
			doom::ui::PrintText("Success To ExportTexture as DDS ( %s )", destinationPath.string().c_str());
		}

	}
	else
	{
		doom::ui::PrintText("Fail To Compress Texture");
	}
}

void doom::assetExporter::assetExporterTexture::ExportTextureAsDDS
(
	const doom::graphics::Texture* const exportedTexture,
	const INT32 lodLevel,
	const doom::graphics::Texture::ePixelFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath
)
{
	D_ASSERT(IsValid(exportedTexture) == true);

	DirectX::Image dxImage = ConvertToDirectXImage(exportedTexture, lodLevel, pixelFormat, dataType);
	ExportTextureAsDDS(dxImage, lodLevel, pixelFormat, dataType, exportPath);
}

void doom::assetExporter::assetExporterTexture::ExportTextureAsDDS
(
	const INT32 lodLevel, 
	UINT8* pixels,
	const SIZE_T width, 
	const SIZE_T height, 
	const doom::graphics::Texture::ePixelFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType, 
	const std::filesystem::path& exportPath)
{

	DirectX::Image dxImage = ConvertToDirectXImage(lodLevel, pixels, width, height, pixelFormat, dataType);
	ExportTextureAsDDS(dxImage, lodLevel, pixelFormat, dataType, exportPath);
}

void doom::assetExporter::assetExporterTexture::ExportTexture
(
	DirectX::Image dxImage, 
	const INT32 lodLevel,
	const doom::graphics::Texture::ePixelFormat pixelFormat, 
	const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath, 
	const eTextureExtension textureExtension
)
{
	std::unique_ptr<UINT8[]> pixels(dxImage.pixels); // for safety

	std::filesystem::path destinationPath = exportPath;
	DirectX::WICCodecs codec;

	switch (textureExtension)
	{
	case eTextureExtension::BMP:
		codec = DirectX::WIC_CODEC_BMP;
		destinationPath.replace_extension(".bmp");
		break;

	case eTextureExtension::GIF:
		codec = DirectX::WIC_CODEC_GIF;
		destinationPath.replace_extension(".gif");
		break;

	case eTextureExtension::JPEG:
		codec = DirectX::WIC_CODEC_JPEG;
		destinationPath.replace_extension(".jpeg");
		break;

	case eTextureExtension::PNG:
		codec = DirectX::WIC_CODEC_PNG;
		destinationPath.replace_extension(".png");
		break;

	case eTextureExtension::TIFF:
		codec = DirectX::WIC_CODEC_TIFF;
		destinationPath.replace_extension(".tiff");
		break;
	}
	
	HRESULT hr = DirectX::SaveToWICFile(
		dxImage,
		DirectX::WIC_FLAGS_NONE,
		DirectX::GetWICCodec(codec),
		destinationPath.generic_wstring().c_str()
	);
	
	D_ASSERT(FAILED(hr) == false);
	if (FAILED(hr) == true)
	{
		doom::ui::PrintText("Fail To ExportTexture ( %s )", destinationPath.string().c_str());
	}
	else
	{
		doom::ui::PrintText("Success To ExportTexture ( %s )", destinationPath.string().c_str());
	}
}

void doom::assetExporter::assetExporterTexture::ExportTexture
(
	const doom::graphics::Texture* const exportedTexture,
	const INT32 lodLevel,
	const doom::graphics::Texture::ePixelFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath,
	const eTextureExtension textureExtension
)
{
	D_ASSERT(IsValid(exportedTexture) == true);

	DirectX::Image dxImage = ConvertToDirectXImage(exportedTexture, lodLevel, pixelFormat, dataType);
	ExportTexture(dxImage, lodLevel, pixelFormat, dataType, exportPath, textureExtension);
}

void doom::assetExporter::assetExporterTexture::ExportTexture
(
	const INT32 lodLevel, 
	UINT8* pixels, 
	const SIZE_T width,
	const SIZE_T height, 
	const doom::graphics::Texture::ePixelFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath,
	const eTextureExtension textureExtension
)
{
	DirectX::Image dxImage = ConvertToDirectXImage(lodLevel, pixels, width, height, pixelFormat, dataType);
	ExportTexture(dxImage, lodLevel, pixelFormat, dataType, exportPath, textureExtension);
}
