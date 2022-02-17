#pragma once

#include <Core.h>

#include <filesystem>

#include <Rendering/Texture/TextureView.h>


namespace DirectX
{
	struct Image;
}

namespace dooms
{
	namespace graphics
	{
		class TextureView;
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
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const std::filesystem::path& exportPath,
				const bool releasePixelMemoryAfterExport = false
			);

			extern void ExportTextureFromTextureAsDDS
			(
				const dooms::graphics::TextureView* const exportedTexture,
				const INT32 lodLevel,
				const std::filesystem::path& exportPath
			);

			extern void ExportTextureAsDDS
			(
				const INT32 lodLevel,
				UINT8* pixels,
				const INT32 width,
				const INT32 height,
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
				const std::filesystem::path& exportPath
			);


			extern void ExportTextureFromMainFrameBufferAsDDS
			(
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
				const std::filesystem::path& exportPath
			);

			extern void ExportTextureFromMainFrameBufferAsDDS
			(
				const INT32 startX,
				const INT32 startY,
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
				const std::filesystem::path& exportPath
			);

			extern void ExportTextureFromMainFrameBufferAsDDS
			(
				const INT32 startX,
				const INT32 startY,
				const INT32 width,
				const INT32 height,
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
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
				const dooms::graphics::TextureView* const exportedTexture,
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
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromFrameBuffer
			(
				const graphics::FrameBuffer* const frameBuffer,
				const UINT32 colorAttachmentIndex,
				const INT32 startX,
				const INT32 startY,
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
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
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromMainFrameBuffer
			(
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromMainFrameBuffer
			(
				const INT32 startX,
				const INT32 startY,
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);

			extern void ExportTextureFromMainFrameBuffer
			(
				const INT32 startX,
				const INT32 startY,
				const INT32 width,
				const INT32 height,
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType,
				const std::filesystem::path& exportPath,
				const eTextureExtension textureExtension
			);
		};
	}
}


