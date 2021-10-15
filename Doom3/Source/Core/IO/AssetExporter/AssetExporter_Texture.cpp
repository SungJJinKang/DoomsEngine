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
				const doom::graphics::eTextureComponentFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType
			)
			{
				DirectX::Image dxImage;
				dxImage.width = width;
				dxImage.height = height;
				dxImage.pixels = pixels;

				switch (pixelFormat)
				{
				case doom::graphics::eTextureComponentFormat::RED:
					if (dataType == doom::graphics::Texture::eDataType::UNSIGNED_BYTE)
					{
						dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;

					}
					else if (dataType == doom::graphics::Texture::eDataType::FLOAT)
					{
						dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
					}
					else
					{
						D_ASSERT(0);
					}
					break;

				case doom::graphics::eTextureComponentFormat::RG:
					if (dataType == doom::graphics::Texture::eDataType::UNSIGNED_BYTE)
					{
						dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R8G8_UNORM;

					}
					else if (dataType == doom::graphics::Texture::eDataType::FLOAT)
					{
						dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
					}
					else
					{
						D_ASSERT(0);
					}
					break;

				case doom::graphics::eTextureComponentFormat::RGB: // RGS also use DXGI_FORMAT_R8G8B8A8_UNORM
				case doom::graphics::eTextureComponentFormat::RGBA:
					if(dataType == doom::graphics::Texture::eDataType::UNSIGNED_BYTE)
					{
						dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
						
					}
					else if (dataType == doom::graphics::Texture::eDataType::FLOAT)
					{
						dxImage.format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
					}
					else
					{
						D_ASSERT(0);
					}
					break;

				case doom::graphics::eTextureComponentFormat::DEPTH_COMPONENT: // RGS also use DXGI_FORMAT_R8G8B8A8_UNORM
					dxImage.format = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
					break;

				case doom::graphics::eTextureComponentFormat::DEPTH_STENCIL:
					dxImage.format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
					break;

				default:
					NEVER_HAPPEN;
				}

				DirectX::ComputePitch(dxImage.format, dxImage.width, dxImage.height, dxImage.rowPitch, dxImage.slicePitch);

				return dxImage;
			}


			DirectX::Image ConvertToDirectXImage
			(
				const doom::graphics::Texture* const exportedTexture,
				const INT32 lodLevel
			)
			{
				D_ASSERT(IsValid(exportedTexture) == true);
				
				return ConvertToDirectXImage(
					lodLevel,
					exportedTexture->GetTexturePixelsUnsafe(lodLevel),
					exportedTexture->GetTextureMetaDataINT32(lodLevel, graphics::Texture::eTextureMataDataType::TEXTURE_WIDTH),
					exportedTexture->GetTextureMetaDataINT32(lodLevel, graphics::Texture::eTextureMataDataType::TEXTURE_HEIGHT),
					exportedTexture->GetDataFormat(),
					exportedTexture->GetDataType()
				);

			}
		}
	}
}


void doom::assetExporter::assetExporterTexture::ExportTextureAsDDS
(
	const DirectX::Image dxImage,
	const INT32 lodLevel,
	const doom::graphics::eTextureComponentFormat pixelFormat,
	const std::filesystem::path& exportPath,
	const bool releasePixelMemoryAfterExport
)
{
	std::unique_ptr<UINT8[]> pixels(dxImage.pixels); // for safety

	DXGI_FORMAT compressFormat;

	switch (pixelFormat)
	{
	case doom::graphics::eTextureComponentFormat::RED:
		compressFormat = DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM;
		break;

	case doom::graphics::eTextureComponentFormat::RG:
		compressFormat = DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM;
		break;

	case doom::graphics::eTextureComponentFormat::RGB:
		compressFormat = DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM;
		break;

	case doom::graphics::eTextureComponentFormat::RGBA:
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

	if (releasePixelMemoryAfterExport == true)
	{
		delete[] dxImage.pixels;
	}
}

void doom::assetExporter::assetExporterTexture::ExportTextureFromTextureAsDDS
(
	const doom::graphics::Texture* const exportedTexture,
	const INT32 lodLevel,
	const std::filesystem::path& exportPath
)
{
	D_ASSERT(IsValid(exportedTexture) == true);

	DirectX::Image dxImage = ConvertToDirectXImage(exportedTexture, lodLevel);
	ExportTextureAsDDS(dxImage, lodLevel, exportedTexture->GetDataFormat(), exportPath);
}

void doom::assetExporter::assetExporterTexture::ExportTextureAsDDS
(
	const INT32 lodLevel, 
	UINT8* pixels,
	const SIZE_T width, 
	const SIZE_T height, 
	const doom::graphics::eTextureComponentFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType, 
	const std::filesystem::path& exportPath)
{

	DirectX::Image dxImage = ConvertToDirectXImage(lodLevel, pixels, width, height, pixelFormat, dataType);
	ExportTextureAsDDS(dxImage, lodLevel, pixelFormat, exportPath);
}

void doom::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBufferAsDDS
(
	const doom::graphics::eTextureComponentFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath
)
{

	ExportTextureFromMainFrameBufferAsDDS(0, 0, pixelFormat, dataType, exportPath);
}

void doom::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBufferAsDDS
(
	const INT32 startX,
	const INT32 startY, 
	const doom::graphics::eTextureComponentFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType, 
	const std::filesystem::path& exportPath
)
{
	doom::graphics::FrameBuffer::UnBindFrameBuffer();

	INT32 dims[4] = { 0, 0 , 0, 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	const INT32 frameBufferWidth = dims[2];;
	const INT32 frameBufferHeight = dims[3];

	ExportTextureFromMainFrameBufferAsDDS(startX, startY, frameBufferWidth, frameBufferHeight, pixelFormat, dataType, exportPath);
}

void doom::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBufferAsDDS
(
	const INT32 startX,
	const INT32 startY, 
	const INT32 width,
	const INT32 height,
	const doom::graphics::eTextureComponentFormat pixelFormat, 
	const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath
)
{
	doom::graphics::FrameBuffer::UnBindFrameBuffer();
	doom::graphics::FrameBuffer::BindFrameBufferStatic(graphics::FrameBuffer::eBindFrameBufferTarget::READ_FRAMEBUFFER, 0);
	doom::graphics::GraphicsAPI::ReadBuffer(graphics::GraphicsAPI::eBufferMode::FRONT);

	const INT32 bufferSize = doom::graphics::Texture::GetTextureBufferSizeStatic(width, height, pixelFormat, dataType);

	UINT8* pixels = new UINT8[bufferSize];
	glReadPixels(startX, startY, width, height, static_cast<UINT32>(pixelFormat), static_cast<UINT32>(dataType), pixels);

	DirectX::Image directXImage = ConvertToDirectXImage(0, pixels, width, height, pixelFormat, dataType);
	ExportTextureAsDDS(directXImage, 0, pixelFormat, exportPath);

	doom::graphics::GraphicsAPI::ReadBuffer(graphics::GraphicsAPI::eBufferMode::NONE);
}

void doom::assetExporter::assetExporterTexture::ExportTexture
(
	const DirectX::Image dxImage, 
	const INT32 lodLevel,
	const std::filesystem::path& exportPath, 
	const eTextureExtension textureExtension,
	const bool releasePixelMemoryAfterExport
)
{
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

	if (releasePixelMemoryAfterExport == true)
	{
		delete[] dxImage.pixels;
	}
	
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

void doom::assetExporter::assetExporterTexture::ExportTextureFromTexture
(
	const doom::graphics::Texture* const exportedTexture,
	const INT32 lodLevel,
	const std::filesystem::path& exportPath,
	const eTextureExtension textureExtension
)
{
	D_ASSERT(IsValid(exportedTexture) == true);

	DirectX::Image dxImage = ConvertToDirectXImage(exportedTexture, lodLevel);
	ExportTexture(dxImage, lodLevel, exportPath, textureExtension);
}

void doom::assetExporter::assetExporterTexture::ExportTexture
(
	const INT32 lodLevel, 
	UINT8* pixels, 
	const SIZE_T width,
	const SIZE_T height, 
	const doom::graphics::eTextureComponentFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath,
	const eTextureExtension textureExtension
)
{
	DirectX::Image dxImage = ConvertToDirectXImage(lodLevel, pixels, width, height, pixelFormat, dataType);
	ExportTexture(dxImage, lodLevel, exportPath, textureExtension);
}

void doom::assetExporter::assetExporterTexture::ExportTextureFromFrameBuffer
(
	const graphics::FrameBuffer* const frameBuffer, const UINT32 colorAttachmentIndex,
	const INT32 startX, const INT32 startY, 
	const doom::graphics::eTextureComponentFormat pixelFormat, const doom::graphics::Texture::eDataType dataType, 
	const std::filesystem::path& exportPath, const eTextureExtension textureExtension
)
{
	frameBuffer->BindFrameBuffer();
	doom::graphics::GraphicsAPI::ReadBuffer(static_cast<graphics::GraphicsAPI::eBufferMode>(static_cast<UINT32>(graphics::GraphicsAPI::eBufferMode::COLOR_ATTACHMENT0) + colorAttachmentIndex));

	INT32 width = frameBuffer->GetFrameBufferParameteriv(doom::graphics::FrameBuffer::eFrameBufferParameterPName::FRAMEBUFFER_DEFAULT_WIDTH);
	INT32 height = frameBuffer->GetFrameBufferParameteriv(doom::graphics::FrameBuffer::eFrameBufferParameterPName::FRAMEBUFFER_DEFAULT_HEIGHT);

	const INT32 bufferSize = doom::graphics::Texture::GetTextureBufferSizeStatic(width, height, pixelFormat, dataType);

	UINT8* pixels = new UINT8[bufferSize];
	glReadPixels(startX, startY, width, height, static_cast<UINT32>(pixelFormat), static_cast<UINT32>(dataType), pixels);

	DirectX::Image directXImage = ConvertToDirectXImage(0, pixels, width, height, pixelFormat, dataType);
	ExportTexture(directXImage, 0, exportPath, textureExtension);

	doom::graphics::GraphicsAPI::ReadBuffer(graphics::GraphicsAPI::eBufferMode::NONE);

}

void doom::assetExporter::assetExporterTexture::ExportTextureFromFrameBuffer
(
	const graphics::FrameBuffer* const frameBuffer, const UINT32 colorAttachmentIndex, 
	const INT32 startX, const INT32 startY,
	const SIZE_T width, const SIZE_T height, const doom::graphics::eTextureComponentFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType, const std::filesystem::path& exportPath,
	const eTextureExtension textureExtension
)
{
	frameBuffer->BindFrameBuffer();
	doom::graphics::GraphicsAPI::ReadBuffer(static_cast<graphics::GraphicsAPI::eBufferMode>(static_cast<UINT32>(graphics::GraphicsAPI::eBufferMode::COLOR_ATTACHMENT0) + colorAttachmentIndex));

	const INT32 bufferSize = doom::graphics::Texture::GetTextureBufferSizeStatic(width, height, pixelFormat, dataType);

	UINT8* pixels = new UINT8[bufferSize];
	glReadPixels(startX, startY, width, height, static_cast<UINT32>(pixelFormat), static_cast<UINT32>(dataType), pixels);

	DirectX::Image directXImage = ConvertToDirectXImage(0, pixels, width, height, pixelFormat, dataType);
	ExportTexture(directXImage, 0, exportPath, textureExtension);

	doom::graphics::GraphicsAPI::ReadBuffer(graphics::GraphicsAPI::eBufferMode::NONE);

}

void doom::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBuffer
(
	const doom::graphics::eTextureComponentFormat pixelFormat, const doom::graphics::Texture::eDataType dataType,
	const std::filesystem::path& exportPath, const eTextureExtension textureExtension)
{
	ExportTextureFromMainFrameBuffer(0, 0, pixelFormat, dataType, exportPath, textureExtension);
}

void doom::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBuffer
(
	const INT32 startX, const INT32 startY,
	const doom::graphics::eTextureComponentFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType, const std::filesystem::path& exportPath,
	const eTextureExtension textureExtension
)
{
	doom::graphics::FrameBuffer::UnBindFrameBuffer();

	INT32 dims[4] = { 0, 0 , 0, 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	const INT32 frameBufferWidth = dims[2];;
	const INT32 frameBufferHeight = dims[3];
	
	ExportTextureFromMainFrameBuffer(startX, startY, frameBufferWidth, frameBufferHeight, pixelFormat, dataType, exportPath, textureExtension);
}


void doom::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBuffer
(
	const INT32 startX, const INT32 startY,
	const INT32 width, const INT32 height, const doom::graphics::eTextureComponentFormat pixelFormat,
	const doom::graphics::Texture::eDataType dataType, const std::filesystem::path& exportPath,
	const eTextureExtension textureExtension
)
{
	doom::graphics::FrameBuffer::UnBindFrameBuffer();
	doom::graphics::FrameBuffer::BindFrameBufferStatic(graphics::FrameBuffer::eBindFrameBufferTarget::READ_FRAMEBUFFER, 0);
	doom::graphics::GraphicsAPI::ReadBuffer(graphics::GraphicsAPI::eBufferMode::FRONT);

	const INT32 bufferSize = doom::graphics::Texture::GetTextureBufferSizeStatic(width, height, pixelFormat, dataType);

	UINT8* pixels = new UINT8[bufferSize];
	glReadPixels(startX, startY, width, height, static_cast<UINT32>(pixelFormat), static_cast<UINT32>(dataType), pixels);

	DirectX::Image directXImage = ConvertToDirectXImage(0, pixels, width, height, pixelFormat, dataType);

	DirectX::ScratchImage rotatedDirectXScratchImage;
	DirectX::FlipRotate(directXImage, DirectX::TEX_FR_FLAGS::TEX_FR_FLIP_VERTICAL, rotatedDirectXScratchImage);

	delete[] directXImage.pixels;
	
	ExportTexture(*rotatedDirectXScratchImage.GetImage(0, 0, 0), 0, exportPath, textureExtension, false);

	doom::graphics::GraphicsAPI::ReadBuffer(graphics::GraphicsAPI::eBufferMode::NONE);

	rotatedDirectXScratchImage.Release();
}
