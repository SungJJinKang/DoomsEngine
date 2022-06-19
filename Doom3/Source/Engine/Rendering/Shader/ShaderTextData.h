#pragma once

#include <Core.h>

#include <string>
#include <filesystem>

#include "Graphics/Graphics_Core.h"
#include "Asset/Utility/ShaderAsset/shaderReflectionDataParser.h"

namespace dooms
{
	namespace asset
	{
		struct FShaderTextData
		{
			std::filesystem::path mShaderTextFilePath;
			dooms::graphics::GraphicsAPI::eGraphicsAPIType ShaderTextGraphicsAPIType;
			std::string ShaderStringText;
			std::string ShaderReflectionDataStringText;
			shaderReflectionDataParser::ShaderReflectionData ShaderReflectionData;

			FShaderTextData();

			FShaderTextData
			(
				const std::string& shaderStringText,
				const std::string& shaderReflectionDataStringText
			);

			FShaderTextData
			(
				const dooms::graphics::GraphicsAPI::eGraphicsAPIType graphicsAPIType,
				const std::string& shaderStringText,
				const std::string& shaderReflectionDataStringText
			);

			void Clear();
			bool IsCompileliable() const;

			bool LoadShaderReflectionDataFromTextIfNotLoaded();
		};
	}
}
