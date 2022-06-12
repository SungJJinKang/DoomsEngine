#include "ShaderTextData.h"

dooms::asset::FShaderTextData::FShaderTextData()
	:
	ShaderTextGraphicsAPIType{ dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE },
	ShaderStringText{},
	ShaderReflectionData{}
{

}

dooms::asset::FShaderTextData::FShaderTextData(const std::string& shaderStringText,const std::string& shaderReflectionDataStringText)
	:
	ShaderTextGraphicsAPIType{ dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE },
	ShaderStringText{ shaderStringText },
	ShaderReflectionDataStringText(shaderReflectionDataStringText),
	ShaderReflectionData{}
{

}

dooms::asset::FShaderTextData::FShaderTextData(const dooms::graphics::GraphicsAPI::eGraphicsAPIType graphicsAPIType,const std::string& shaderStringText, const std::string& shaderReflectionDataStringText)
	:
	ShaderTextGraphicsAPIType{ graphicsAPIType },
	ShaderStringText{ shaderStringText },
	ShaderReflectionDataStringText(shaderReflectionDataStringText),
	ShaderReflectionData{}
{

}

void dooms::asset::FShaderTextData::Clear()
{
	ShaderTextGraphicsAPIType = dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE;
	ShaderStringText.clear();
	ShaderReflectionDataStringText.clear();
	ShaderReflectionData.Clear();
}

bool dooms::asset::FShaderTextData::IsCompileliable() const
{
	return
		(ShaderStringText.empty() == false) &&
		(ShaderTextGraphicsAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE) &&
		(ShaderReflectionData.mIsGenerated == true);
}

bool dooms::asset::FShaderTextData::LoadShaderReflectionDataFromTextIfNotLoaded()
{
	bool isLoaded = false;

	if ((ShaderReflectionDataStringText.empty() == false) && (ShaderReflectionData.mIsGenerated == false))
	{
		ShaderReflectionData = dooms::asset::shaderReflectionDataParser::ParseShaderReflectionStringText(ShaderReflectionDataStringText);
		isLoaded = ShaderReflectionData.mIsGenerated;
	}

	return isLoaded;
}
