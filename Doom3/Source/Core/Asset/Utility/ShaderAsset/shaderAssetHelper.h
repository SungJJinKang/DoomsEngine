#pragma once

#include <filesystem>
#include <string>

#include "Graphics/GraphicsAPI/GraphicsAPI.h"

namespace dooms
{
	namespace asset
	{
		namespace shaderAssetHelper
		{
			extern bool CheckIsSharpInclude(const std::string& str);
			extern std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> ParseShaderTextStringsBasedOnTargetGraphicsPipeLineStage(const std::filesystem::path& shaderAssetPath, const std::string& shaderText);
			extern std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> ParseShaderReflectionTextStringsBasedOnTargetGraphicsPipeLineStage(const std::string& shaderReflectionText);
			extern std::string ExtractShaderFile(const std::filesystem::path& path);
			extern dooms::graphics::GraphicsAPI::eGraphicsAPIType GetShaderAssetGraphicsAPIType(const std::string& shaderAssetFileExtension);
		}
	}
}

