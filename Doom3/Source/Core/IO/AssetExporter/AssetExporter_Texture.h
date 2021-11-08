#pragma once

#include <Doom_Core.h>

#include <filesystem>

#include <Graphics/Texture/Texture.h>


namespace DirectX
{
	struct Image;
}

namespace dooms
{
	namespace graphics
	{
		class Texture;
		class FrameBuffer;
	}

	namespace assetExporter
	{
		namespace assetExporterTexture
		{
			extern void ExportTextureAsDDS
			(
				const DirectX::Image dxImage,
				const INT32 lodLevel,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const std::filesystem::path& exportPath,
				const bool releasePixelMemoryAfterExport = false
			);

			extern void ExportTextureFromTextureAsDDS
			(
				const dooms::graphics::Texture* const exportedTexture,
				const INT32 lodLevel,
				const std::filesystem::path& exportPath
			);

			extern void ExportTextureAsDDS
			(
				const INT32 lodLevel,
				UINT8* pixels,
				const INT32 width,
				const INT32 height,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath
			);


			extern void ExportTextureFromMainFrameBufferAsDDS
			(
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath
			);

			extern void ExportTextureFromMainFrameBufferAsDDS
			(
				const INT32 startX,
				const INT32 startY,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath
			);

			extern void ExportTextureFromMainFrameBufferAsDDS
			(
				const INT32 startX,
				const INT32 startY,
				const INT32 width,
				const INT32 height,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath
			);

			enum class D_ENUM eTextureExtension
			{
				BMP,
				PNG,
				GIF,
				TIFF,
				JPEG
			};

			extern void ExportTexture
			(
				const DirectX::Image dxImage,
				const INT32 lodLevel,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension,
				const bool releasePixelMemoryAfterExport = false
			);

			extern void ExportTextureFromTexture
			(
				const dooms::graphics::Texture* const exportedTexture,
				const INT32 lodLevel,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTexture
			(
				const INT32 lodLevel,
				UINT8* pixels,
				const INT32 width,
				const INT32 height,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromFrameBuffer
			(
				const graphics::FrameBuffer* const frameBuffer,
				const UINT32 colorAttachmentIndex,
				const INT32 startX,
				const INT32 startY,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromFrameBuffer
			(
				const graphics::FrameBuffer* const frameBuffer,
				const UINT32 colorAttachmentIndex,
				const INT32 startX,
				const INT32 startY,
				const INT32 width,
				const INT32 height,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromMainFrameBuffer
			(
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromMainFrameBuffer
			(
				const INT32 startX,
				const INT32 startY,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromMainFrameBuffer
			(
				const INT32 startX,
				const INT32 startY,
				const INT32 width,
				const INT32 height,
				const dooms::graphics::eTextureComponentFormat pixelFormat,
				const dooms::graphics::Texture::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);
		};
	}
}


