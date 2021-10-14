#include "ExportTextureTester.h"

#include "Rendering/Camera.h"

#include <IO/AssetExporter/AssetExporter_Texture.h>

void doom::ExportTextureTester::InitComponent()
{
	PlainComponent::InitComponent();
}

void doom::ExportTextureTester::UpdateComponent()
{
	PlainComponent::UpdateComponent();

	if(doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F2))
	{
		doom::ui::PrintText("Export Camera Texture");

		doom::graphics::SingleTexture* texture = 
			doom::Camera::GetMainCamera()->mDefferedRenderingFrameBuffer.GetFrameBufferTexture
			(
				doom::graphics::GraphicsAPI::eBufferBitType::COLOR, 
				0
			);

		doom::assetExporter::assetExporterTexture::ExportTexture(
			texture,
			0,
			doom::graphics::Texture::ePixelFormat::RGBA,
			doom::graphics::Texture::eDataType::UNSIGNED_BYTE,
			std::filesystem::current_path(),
			assetExporter::assetExporterTexture::eTextureExtension::PNG
		);
	}

}
