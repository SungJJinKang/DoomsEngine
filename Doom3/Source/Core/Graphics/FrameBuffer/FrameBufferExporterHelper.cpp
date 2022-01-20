#include "FrameBufferExporterHelper.h"

#include "Rendering/Camera.h"
#include <EngineGUI/PrintText.h>

void dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferColor
(
	const std::filesystem::path& path,
	const assetExporter::assetExporterTexture::eTextureExtension extension
)
{
	dooms::ui::PrintText("Export Main FrameBuffer Texture");
				
	dooms::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBuffer
	(
		GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA,
		dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE,
		std::filesystem::current_path(),
		extension
	);
}

void dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferColorAsDDS(const std::filesystem::path& path)
{
	dooms::ui::PrintText("Export Main FrameBuffer Texture As DDS");

	dooms::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBufferAsDDS
	(
		dooms::graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA,
		dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE,
		std::filesystem::current_path()
	);
}

void dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferDepth(const std::filesystem::path& path,
	const assetExporter::assetExporterTexture::eTextureExtension extension)
{

	dooms::ui::PrintText("Export Main FrameBuffer Depth Texture");

	dooms::graphics::Texture* depthTexture =
		dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(dooms::graphics::GraphicsAPI::eBufferBitType::DEPTH_BUFFER, 0);
	dooms::assetExporter::assetExporterTexture::ExportTextureFromTexture
	(
		depthTexture,
		0,
		std::filesystem::current_path(),
		extension
	);
}

void dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferDepthAsDDS(const std::filesystem::path& path)
{
	dooms::ui::PrintText("Export Main FrameBuffer Depth Texture As DDS");

	dooms::graphics::Texture* depthTexture =
		dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture(dooms::graphics::GraphicsAPI::eBufferBitType::DEPTH_BUFFER, 0);
	dooms::assetExporter::assetExporterTexture::ExportTextureFromTextureAsDDS
	(
		depthTexture,
		0,
		std::filesystem::current_path()
	);
}
