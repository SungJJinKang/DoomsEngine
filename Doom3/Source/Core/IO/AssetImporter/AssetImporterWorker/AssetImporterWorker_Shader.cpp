#include "AssetImporterWorker_Shader.h"

#include <TextImporter.h>

#include <Asset/ShaderAsset.h>

bool doom::assetimporter::AssetImporterWorker_Shader::ImportShaderAsset
(
	const std::filesystem::path& path,
	doom::asset::ShaderAsset* const shaderAsset
)
{
	std::string text{};
	bool isSuccess = GetTextFromFile(path, text);

	D_ASSERT(text.empty() == false);

	if (isSuccess)
	{
		shaderAsset->SetShaderText(text, false);
		return true;
	}
	else
	{
		return false;
	}
}


bool doom::assetimporter::AssetImporterWorker_Shader::ImportSpecificAsset(const std::filesystem::path& path, doom::asset::Asset* asset)
{
	return ImportShaderAsset(path, static_cast<doom::asset::ShaderAsset*>(asset));
}

doom::asset::eAssetType doom::assetimporter::AssetImporterWorker_Shader::GetEAssetType() const
{
	return doom::asset::eAssetType::SHADER;
}

