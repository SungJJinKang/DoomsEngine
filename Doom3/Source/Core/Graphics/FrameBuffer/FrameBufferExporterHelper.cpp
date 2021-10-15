#include "FrameBufferExporterHelper.h"

#include "Rendering/Camera.h"

void doom::graphics::FrameBufferExporterHelper::ExportMainFrameBufferColor
(
	const std::filesystem::path& path,
	const assetExporter::assetExporterTexture::eTextureExtension extension
)
{
	doom::ui::PrintText("Export Main FrameBuffer Texture");
				
	doom::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBuffer
	(
		doom::graphics::eTextureComponentFormat::RGBA,
		doom::graphics::Texture::eDataType::UNSIGNED_BYTE,
		std::filesystem::current_path(),
		extension
	);
}

void doom::graphics::FrameBufferExporterHelper::ExportMainFrameBufferColorAsDDS(const std::filesystem::path& path)
{
	doom::ui::PrintText("Export Main FrameBuffer Texture As DDS");

	doom::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBufferAsDDS
	(
		doom::graphics::eTextureComponentFormat::RGBA,
		doom::graphics::Texture::eDataType::UNSIGNED_BYTE,
		std::filesystem::current_path()
	);
}

void doom::graphics::FrameBufferExporterHelper::ExportMainFrameBufferDepth(const std::filesystem::path& path,
	const assetExporter::assetExporterTexture::eTextureExtension extension)
{

	doom::ui::PrintText("Export Main FrameBuffer Depth Texture");

	doom::graphics::SingleTexture* depthTexture =
		doom::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::DEPTH, 0);
	doom::assetExporter::assetExporterTexture::ExportTextureFromTexture
	(
		depthTexture,
		0,
		std::filesystem::current_path(),
		extension
	);
}

void doom::graphics::FrameBufferExporterHelper::ExportMainFrameBufferDepthAsDDS(const std::filesystem::path& path)
{
	doom::ui::PrintText("Export Main FrameBuffer Depth Texture As DDS");

	doom::graphics::SingleTexture* depthTexture =
		doom::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(doom::graphics::GraphicsAPI::eBufferBitType::DEPTH, 0);
	doom::assetExporter::assetExporterTexture::ExportTextureFromTextureAsDDS
	(
		depthTexture,
		0,
		std::filesystem::current_path()
	);
}
