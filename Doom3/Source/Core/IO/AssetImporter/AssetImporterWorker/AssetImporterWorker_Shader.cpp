#include "AssetImporterWorker_Shader.h"

#include <Asset/Utility/textImporter.h>

#include <Asset/ShaderAsset.h>
#include <Asset/Utility/ShaderAsset/shaderAssetHelper.h>

bool dooms::assetImporter::AssetImporterWorker_Shader::ImportShaderAsset
(
	const std::filesystem::path& path,
	dooms::asset::ShaderAsset* const shaderAsset
)
{
	std::string text{};
	bool isSuccess = asset::textImporter::GetTextFromFile(path, text);

	D_ASSERT(text.empty() == false);

	if (isSuccess)
	{
		const dooms::graphics::GraphicsAPI::eGraphicsAPIType shaderAssetGraphicsAPIType = dooms::asset::shaderAssetHelper::GetShaderAssetGraphicsAPIType(path.extension().generic_u8string());
		shaderAsset->SetShaderText(text, shaderAssetGraphicsAPIType, false);
		return true;
	}
	else
	{
		return false;
	}
}

dooms::assetImporter::AssetImporterWorker_Shader::AssetImporterWorker_Shader()
{
	AssetImporterWorker::IsInitialized = true;
}


bool dooms::assetImporter::AssetImporterWorker_Shader::ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset)
{
	return ImportShaderAsset(path, static_cast<dooms::asset::ShaderAsset*>(asset));
}

dooms::asset::eAssetType dooms::assetImporter::AssetImporterWorker_Shader::GetEAssetType() const
{
	return dooms::asset::eAssetType::SHADER;
}

