#include "ExportTextureTester.h"

#include "Rendering/Camera.h"
#include <Rendering/Pipeline/GraphicsPipeLineCamera.h>
#include <Rendering/FrameBuffer/FrameBuffer.h>
#include <Asset/AssetImportExporter/AssetExporter/AssetExporter_Texture.h>
#include <Rendering/FrameBuffer/FrameBufferExporterHelper.h>

void dooms::ExportTextureTester::InitComponent()
{
	Component::InitComponent();
}

void dooms::ExportTextureTester::UpdateComponent()
{
	Component::UpdateComponent();

	if(dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F2))
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
			dooms::graphics::TextureView* texture = dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()->GetCameraFrameBuffer()->GetColorTextureView(0, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER);

			dooms::assetExporter::assetExporterTexture::ExportTextureFromTexture(
				texture,
				0,
				std::filesystem::current_path(),
				assetExporter::assetExporterTexture::eTextureExtension::PNG
			);
			dooms::ui::PrintText("Export Camera Texture");
		}
	}

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F3))
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
			dooms::graphics::TextureView* const texture = dooms::Camera::GetMainCamera()->GetGraphicsPipeLineCamera()->GetCameraFrameBuffer()->GetColorTextureView(0, dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER);

			dooms::assetExporter::assetExporterTexture::ExportTextureFromTextureAsDDS(
				texture,
				0,
				std::filesystem::current_path()
			);

			dooms::ui::PrintText("Export Camera Texture");
		}
	}

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F4))
	{
		dooms::ui::PrintText("Export Main FrameBuffer Texture");
		
		dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferColor
		(
			std::filesystem::current_path(),
			assetExporter::assetExporterTexture::eTextureExtension::PNG
		);
	}

	
	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F5))
	{
		dooms::ui::PrintText("Export Main FrameBuffer Depth Texture");
		
		dooms::graphics::FrameBufferExporterHelper::ExportMainFrameBufferDepth
		(
			std::filesystem::current_path(),
			assetExporter::assetExporterTexture::eTextureExtension::PNG
		);
	}
}
