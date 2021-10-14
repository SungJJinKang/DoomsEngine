#pragma once

#include <Doom_Core.h>

#include <filesystem>

#include <Graphics/Texture/Texture.h>

namespace DirectX
{
	struct Image;
}

namespace doom
{
	namespace graphics
	{
		class Texture;
	}

	namespace assetExporter
	{
		namespace assetExporterTexture
		{
			extern void ExportTextureAsDDS
			(
				DirectX::Image dxImage,
				const INT32 lodLevel,
				const doom::graphics::Texture::ePixelFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath
			);

			extern void ExportTextureAsDDS
			(
				const doom::graphics::Texture* const exportedTexture,
				const INT32 lodLevel,
				const doom::graphics::Texture::ePixelFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath
			);

			extern void ExportTextureAsDDS
			(
				const INT32 lodLevel,
				UINT8* pixels,
				const SIZE_T width,
				const SIZE_T height,
				const doom::graphics::Texture::ePixelFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath
			);
			

			enum class eTextureExtension
			{
				BMP,
				PNG,
				GIF,
				TIFF,
				JPEG
			};

			extern void ExportTexture
			(
				DirectX::Image dxImage,
				const INT32 lodLevel,
				const doom::graphics::Texture::ePixelFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTexture
			(
				const doom::graphics::Texture* const exportedTexture,
				const INT32 lodLevel,
				const doom::graphics::Texture::ePixelFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTexture
			(
				const INT32 lodLevel,
				UINT8* pixels,
				const SIZE_T width,
				const SIZE_T height,
				const doom::graphics::Texture::ePixelFormat pixelFormat,
				const doom::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);
		};
	}
}


