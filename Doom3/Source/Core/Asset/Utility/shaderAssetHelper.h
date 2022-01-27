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
			extern std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> ParseShaderTextStrings(const std::filesystem::path& shaderAssetPath, const std::string& shaderText);
			extern std::string ExtractShaderFile(const std::filesystem::path& path);
		}
	}
}

