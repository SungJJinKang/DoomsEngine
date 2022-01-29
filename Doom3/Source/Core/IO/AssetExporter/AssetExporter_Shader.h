#pragma once

#include <filesystem>
#include <vector>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

namespace dooms
{
	namespace assetExporter
	{
		namespace assetExporterShader
		{
			/**
			 * \brief 
			 * \param originalGlslShaderTextFilePath Original glsl Shader Text File Path
			 * \param toShaderTextGraphisAPIType Target Shader type ( glsl or hlsl ... )
			 * \return Info Data of generated shader files.
			 */
			extern bool GenerateEngineShaderFiles
			(
				const std::filesystem::path& originalGlslShaderTextFilePath,
				const dooms::graphics::GraphicsAPI::eGraphicsAPIType toShaderTextGraphisAPIType
			);

			extern void LoadGlslcc();
			extern void UnloadGlslcc();

			enum class eEngineShaderFileType
			{
				SHADER_TEXT_FILE,
				SHADER_REFLECTION_DATA_JSON_FILE
			};

			extern std::filesystem::path GetEngineShaderFilePath
			(
				const std::filesystem::path& originalShaderFilePath,
				const dooms::graphics::GraphicsAPI::eGraphicsAPIType targetShaderTextGraphisAPIType,
				const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetShaderStageType,
				const eEngineShaderFileType targetFileType
			);
		}
	}
}