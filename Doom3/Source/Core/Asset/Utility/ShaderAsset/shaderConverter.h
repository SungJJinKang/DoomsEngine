#pragma once

#include <string>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

namespace dooms
{
	namespace asset
	{
		namespace shaderConverter
		{
			
			bool ConvertShaderTextFormat
			(
				const std::string& shaderTextStr,
				std::string& outConvertedShaderTextStr,
				const dooms::graphics::GraphicsAPI::eGraphicsAPIType fromShaderTextGraphisAPIType,
				const dooms::graphics::GraphicsAPI::eGraphicsAPIType toShaderTextGraphisAPIType
			);
		}
	}
}
