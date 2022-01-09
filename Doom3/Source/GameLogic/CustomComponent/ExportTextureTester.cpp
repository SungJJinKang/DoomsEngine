#include "ExportTextureTester.h"

#include "Rendering/Camera.h"

#include <IO/AssetExporter/AssetExporter_Texture.h>
#include <Graphics/FrameBuffer/FrameBufferExporterHelper.h>

void dooms::ExportTextureTester::InitComponent()
{
	Component::InitComponent();
}

void dooms::ExportTextureTester::UpdateComponent()
{
	Component::UpdateComponent();

	if(dooms::userinput::UserInput_Server::GetKeyUp(dooms::graphics::GraphicsAPIInput::eKEY_CODE::KEY_F2))
	{
		dooms::ui::PrintText("Export Camera Texture");
		
		dooms::graphics::SingleTexture* texture = 
			dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture
			(
				dooms::graphics::GraphicsAPI::eBufferBitType::COLOR_BUFFER,
				0
			);

		dooms::assetExporter::assetExporterTexture::ExportTextureFromTexture(
			texture,
			0,
			std::filesystem::current_path(),
			assetExporter::assetExporterTexture::eTextureExtension::PNG
		);
	}

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::graphics::GraphicsAPIInput::eKEY_CODE::KEY_F3))
	{
		dooms::ui::PrintText("Export Camera Texture");

		dooms::graphics::SingleTexture* texture =
			dooms::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture
			(
				dooms::graphics::GraphicsAPI::eBufferBitType::COLOR_BUFFER,
				0
			);

		dooms::assetExporter::assetExporterTexture::ExportTextureFromTextureAsDDS(
			texture,
			0,
			std::filesystem::current_path()
		);
	}

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::graphics::GraphicsAPIInput::eKEY_CODE::KEY_F4))
	{
		dooms::ui::PrintText("Export Main FrameBuffer Texture");
		
		dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferColor
		(
			std::filesystem::current_path(),
			assetExporter::assetExporterTexture::eTextureExtension::PNG
		);
	}

	
	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::graphics::GraphicsAPIInput::eKEY_CODE::KEY_F5))
	{
		dooms::ui::PrintText("Export Main FrameBuffer Depth Texture");
		
		dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferDepth
		(
			std::filesystem::current_path(),
			assetExporter::assetExporterTexture::eTextureExtension::PNG
		);
	}
}
