#pragma once
#include <filesystem>

#include "AssetExporter/AssetExporter_Texture.h"

namespace doom
{
	namespace graphics
	{
		namespace FrameBufferExporterHelper
		{
			void ExportMainFrameBufferColor
			(
				const std::filesystem::path& path, 
				const assetExporter::assetExporterTexture::eTextureExtension extension
			);

			void ExportMainFrameBufferColorAsDDS
			(
				const std::filesystem::path& path
			);

			void ExportMainFrameBufferDepth
			(
				const std::filesystem::path& path,
				const assetExporter::assetExporterTexture::eTextureExtension extension
			);

			void ExportMainFrameBufferDepthAsDDS
			(
				const std::filesystem::path& path
			);
		};
	}
}

