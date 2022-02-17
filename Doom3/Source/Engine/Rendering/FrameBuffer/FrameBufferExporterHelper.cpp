#include "FrameBufferExporterHelper.h"

#include "Rendering/Camera.h"
#include <Rendering/FrameBuffer/FrameBuffer.h>
#include "Rendering/Pipeline/GraphicsPipeLineCamera.h"
#include <EngineGUI/PrintText.h>

void dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferColor
(
	const std::filesystem::path& path,
	const assetExporter::assetExporterTexture::eTextureExtension extension
)
{
	dooms::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBuffer
	(
		GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA,
		dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE,
		std::filesystem::current_path(),
		extension
	);

	dooms::ui::PrintText("Export Main FrameBuffer Texture");
}

void dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferColorAsDDS(const std::filesystem::path& path)
{
	dooms::assetExporter::assetExporterTexture::ExportTextureFromMainFrameBufferAsDDS
	(
		dooms::graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA,
		dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE,
		std::filesystem::current_path()
	);

	dooms::ui::PrintText("Export Main FrameBuffer Texture As DDS");
}

void dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferDepth
(
	const std::filesystem::path& path,
	const assetExporter::assetExporterTexture::eTextureExtension extension
)
{
	D_ASSERT
	(
		IsValid(dooms::Camera::GetMainCamera()) &&
		IsValid(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()) &&
		IsValid(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()->GetCameraFrameBuffer())
	);
	if
	(
		IsValid(dooms::Camera::GetMainCamera()) &&
		IsValid(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()) &&
		IsValid(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()->GetCameraFrameBuffer()) 
	)
	{
		dooms::graphics::TextureView* depthTexture =
			dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()->GetCameraFrameBuffer()->GetDepthTextureView(0, GraphicsAPI::PIXEL_SHADER);
		dooms::assetExporter::assetExporterTexture::ExportTextureFromTexture
		(
			depthTexture,
			0,
			std::filesystem::current_path(),
			extension
		);

		dooms::ui::PrintText("Export Main FrameBuffer Depth Texture");
	}
	
}

void dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferDepthAsDDS(const std::filesystem::path& path)
{
	D_ASSERT
	(
		IsValid(dooms::Camera::GetMainCamera()) &&
		IsValid(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()) &&
		IsValid(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()->GetCameraFrameBuffer())
	);
	if
	(
		IsValid(dooms::Camera::GetMainCamera()) &&
		IsValid(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()) &&
		IsValid(dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()->GetCameraFrameBuffer())
	)
	{
		dooms::graphics::TextureView* depthTexture =
			dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()->GetCameraFrameBuffer()->GetDepthTextureView(0, GraphicsAPI::PIXEL_SHADER);
		dooms::assetExporter::assetExporterTexture::ExportTextureFromTextureAsDDS
		(
			depthTexture,
			0,
			std::filesystem::current_path()
		);

		dooms::ui::PrintText("Export Main FrameBuffer Depth Texture As DDS");
	}
}
