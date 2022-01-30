#include "AssetImporterWorker_Shader.h"

#include <EngineGUI/PrintText.h>
#include <Asset/Utility/textImporter.h>
#include <Asset/ShaderAsset.h>
#include <Asset/Utility/ShaderAsset/shaderAssetHelper.h>
#include <IO/AssetExporter/AssetExporter_Shader.h>
#include <Asset/Utility/textImporter.h>
#include <magic_enum.hpp>

bool dooms::assetImporter::AssetImporterWorker_Shader::IsEssentialEngineShaderFilesExist
(
	const std::filesystem::path& assetPath
) const
{
	// Shader require at least vertex, fragment shader.

	bool isEngineShaderFilesExist = true;

	static const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage essentialPipeLineStages[4]
	{
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER,
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER,
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER,
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER,
	};

	static const assetExporter::assetExporterShader::eEngineShaderFileType essentialEngineShaderFileType[4]
	{
		assetExporter::assetExporterShader::eEngineShaderFileType::SHADER_TEXT_FILE,
		assetExporter::assetExporterShader::eEngineShaderFileType::SHADER_REFLECTION_DATA_JSON_FILE,
		assetExporter::assetExporterShader::eEngineShaderFileType::SHADER_TEXT_FILE,
		assetExporter::assetExporterShader::eEngineShaderFileType::SHADER_REFLECTION_DATA_JSON_FILE
	};

	const graphics::GraphicsAPI::eGraphicsAPIType currentGraphicsAPIType = dooms::graphics::GraphicsAPI::GetCurrentAPIType();

	for(size_t i = 0 ; i < 4 ; i++)
	{
		const std::filesystem::path targetEngineShaderFilePath = dooms::assetExporter::assetExporterShader::GetEngineShaderFilePath
		(
			assetPath, currentGraphicsAPIType, essentialPipeLineStages[i], essentialEngineShaderFileType[i]
		);

		isEngineShaderFilesExist &= std::filesystem::exists(targetEngineShaderFilePath);
		
		if(isEngineShaderFilesExist == false)
		{
			dooms::ui::PrintText("Essential engine shader file doesn't exist ( Shader Type : %s, Shader File Type : %s )", magic_enum::enum_name(essentialPipeLineStages[i]).data(), magic_enum::enum_name(essentialEngineShaderFileType[i]).data());
			break;
		}
	}
	
	return isEngineShaderFilesExist;
}

bool dooms::assetImporter::AssetImporterWorker_Shader::ImportShaderAsset
(
	const std::filesystem::path& assetPath,
	dooms::asset::ShaderAsset* const shaderAsset
)
{
	D_ASSERT(IsValid(shaderAsset));

	bool isSucess = false;
	
	D_ASSERT(assetPath.extension().compare(".glsl") == 0);
	if (assetPath.extension().compare(".glsl") == 0)
	{
		bool isEssentialEngineShaderFilesExist = IsEssentialEngineShaderFilesExist(assetPath);

		if(isEssentialEngineShaderFilesExist == false)
		{
			dooms::ui::PrintText("Engine Shader File doesn't exist ( glsl File Path : %s )", assetPath.generic_u8string().c_str());
			D_DEBUG_LOG(eLogType::D_LOG, "Engine Shader File doesn't exist ( glsl File Path : %s )", assetPath.generic_u8string().c_str());

			const bool isSuccessToGenerateEngineShaderFiles = dooms::assetExporter::assetExporterShader::GenerateEngineShaderFiles(assetPath, dooms::graphics::GraphicsAPI::GetCurrentAPIType());
			D_ASSERT(isSuccessToGenerateEngineShaderFiles == true);

			isEssentialEngineShaderFilesExist |= IsEssentialEngineShaderFilesExist(assetPath);
		}
		
		if(isEssentialEngineShaderFilesExist == true)
		{
			std::array<asset::ShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT> shaderTextDatas = LoadShaderTextDatas(assetPath);

			shaderAsset->SetShaderText(shaderTextDatas, true);
		}
		
	}


	return isSucess;
}

std::array<dooms::asset::ShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT> dooms::assetImporter::AssetImporterWorker_Shader::LoadShaderTextDatas(const std::filesystem::path& assetPath) const
{
	D_ASSERT(IsEssentialEngineShaderFilesExist(assetPath));

	static const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage UsableShaderType[3]
	{
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER,
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER,
		dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::COMPUTE_SHADER
	};

	const graphics::GraphicsAPI::eGraphicsAPIType currentGraphicsAPIType = dooms::graphics::GraphicsAPI::GetCurrentAPIType();

	std::array<dooms::asset::ShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT> shaderTextDatas{};

	for(size_t i = 0 ; i < 3 ; i++)
	{
		const std::filesystem::path shaderTextFilePath = dooms::assetExporter::assetExporterShader::GetEngineShaderFilePath
		(
			assetPath,
			currentGraphicsAPIType,
			UsableShaderType[i],
			dooms::assetExporter::assetExporterShader::eEngineShaderFileType::SHADER_TEXT_FILE
		);
		const std::filesystem::path shaderTextJsonFilePath = dooms::assetExporter::assetExporterShader::GetEngineShaderFilePath
		(
			assetPath,
			currentGraphicsAPIType,
			UsableShaderType[i],
			dooms::assetExporter::assetExporterShader::eEngineShaderFileType::SHADER_REFLECTION_DATA_JSON_FILE
		);

		if (std::filesystem::exists(shaderTextFilePath) == true && std::filesystem::exists(shaderTextJsonFilePath) == true)
		{
			shaderTextDatas[i].mShaderStringText = dooms::asset::textImporter::GetTextFromFile(shaderTextFilePath);
			shaderTextDatas[i].mShaderReflectionDataStringText = dooms::asset::textImporter::GetTextFromFile(shaderTextJsonFilePath);
			shaderTextDatas[i].mShaderTextGraphicsAPIType = currentGraphicsAPIType;
		}
	}

	return shaderTextDatas;
}

dooms::assetImporter::AssetImporterWorker_Shader::AssetImporterWorker_Shader()
{
	AssetImporterWorker::IsInitialized = true;
}


bool dooms::assetImporter::AssetImporterWorker_Shader::ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset)
{
	return ImportShaderAsset(path, CastTo<dooms::asset::ShaderAsset*>(asset));
}

dooms::asset::eAssetType dooms::assetImporter::AssetImporterWorker_Shader::GetEAssetType() const
{
	return dooms::asset::eAssetType::SHADER;
}

