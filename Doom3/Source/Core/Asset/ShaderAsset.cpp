#include <sstream>

#include "ShaderAsset.h"

#include "../Graphics/Material/Material.h"
#include "Utility/shaderAssetHelper.h"
#include <utility/trim.h>
#include <EngineGUI/PrintText.h>
#include "Utility/shaderConverter.h"


dooms::asset::ShaderTextString::ShaderTextString() : mShaderTextGraphicsAPIType{ dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE }, mText{}
{

}

dooms::asset::ShaderTextString::ShaderTextString(const std::string& text) : mShaderTextGraphicsAPIType{ dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE }, mText{ text }
{

}

dooms::asset::ShaderTextString::ShaderTextString
(
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType graphicsAPIType,
	const std::string& text
)
	: mShaderTextGraphicsAPIType{ graphicsAPIType }, mText{ text }
{

}

void dooms::asset::ShaderTextString::Clear()
{
	mShaderTextGraphicsAPIType = dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE;
	mText.clear();
}

bool dooms::asset::ShaderTextString::IsValid() const
{
	return (mText.empty() == false) && (mShaderTextGraphicsAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE);
}

dooms::asset::ShaderAsset::ShaderAsset()
	: mShaderTextStrings(), mShaderObject()
{
}


dooms::asset::ShaderAsset::ShaderAsset(const std::array<ShaderTextString, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderTexts)
	: mShaderTextStrings(shaderTexts), mShaderObject()
{
	CompileShaders();
}

dooms::asset::ShaderAsset::ShaderAsset(ShaderAsset&& shader) noexcept = default;
dooms::asset::ShaderAsset& dooms::asset::ShaderAsset::operator=(ShaderAsset&& shader) noexcept = default;

dooms::asset::ShaderAsset::~ShaderAsset()
{
	DestroyShaderObjects();
	ClearShaderTextStrings();
}

void dooms::asset::ShaderAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();
	
	DestroyShaderObjects();
	ClearShaderTextStrings();
}

void dooms::asset::ShaderAsset::DestroyShaderObjects()
{
	for(auto& shaderObject : mShaderObject)
	{
		if(shaderObject.IsValid())
		{
			graphics::GraphicsAPI::DestroyShaderObject(shaderObject);
			shaderObject.Reset();
		}
	}
}

void dooms::asset::ShaderAsset::ClearShaderTextStrings()
{
	for (ShaderTextString& shaderTextString : mShaderTextStrings)
	{
		shaderTextString.Clear();
	}
}


void dooms::asset::ShaderAsset::SetShaderText
(
	const std::string& shaderStr,
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType shaderTextraphicsAPIType, 
	const bool compileShader
)
{
	D_ASSERT(shaderTextraphicsAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE);

	std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> shaderTexts = shaderAssetHelper::ParseShaderTextStrings(GetAssetPath(), shaderStr);
	for (size_t shaderTextIndex = 0; shaderTextIndex < GRAPHICS_PIPELINE_STAGE_COUNT; shaderTextIndex++)
	{
		mShaderTextStrings[shaderTextIndex].mShaderTextGraphicsAPIType = shaderTextraphicsAPIType;
		mShaderTextStrings[shaderTextIndex].mText = shaderTexts[shaderTextIndex];
	}


	D_ASSERT_LOG
	(
		IsHasAnyValidShaderTextString() == true,
		"Shader Asset doesn't have any shader string ( File Path : %s )", GetAssetPathAsUTF8Str().c_str()
	);
	if (IsHasAnyValidShaderTextString() == false)
	{
		dooms::ui::PrintText("Shader Asset doesn't have any shader string ( File Path : %s )", GetAssetPathAsUTF8Str().c_str());
	}

	if (compileShader == true)
	{
		CompileShaders();
	}
}

bool dooms::asset::ShaderAsset::ConvertShaderTextStringToCurrentGraphicsAPIShaderFormat(ShaderTextString& shaderText)
{
	bool isConvertingSuccess = false;

	D_ASSERT(shaderText.IsValid());
	if (shaderText.IsValid() == true)
	{
		isConvertingSuccess = true;

		const dooms::graphics::GraphicsAPI::eGraphicsAPIType currentShaderTextGraphicsAPIType = shaderText.mShaderTextGraphicsAPIType;
		const dooms::graphics::GraphicsAPI::eGraphicsAPIType currentLoadedGraphicsAPIType = dooms::graphics::GraphicsAPI::GetCurrentAPIType();

		if(currentShaderTextGraphicsAPIType != currentLoadedGraphicsAPIType)
		{
			std::string convertedShaderTextStr{};
			isConvertingSuccess = dooms::asset::shaderConverter::ConvertShaderTextFormat
			(
				shaderText.mText,
				convertedShaderTextStr,
				currentShaderTextGraphicsAPIType, 
				currentLoadedGraphicsAPIType
			);

			D_ASSERT(convertedShaderTextStr.empty() == false);
			shaderText.mText = std::move(convertedShaderTextStr);
		}
	}
	D_ASSERT_LOG(isConvertingSuccess, "Fail to ConvertShaderTextStringToCurrentGraphicsAPIShaderFormat ( Shader Asset Path : %s )", GetAssetPathAsUTF8Str().c_str());

	return isConvertingSuccess;
}

void dooms::asset::ShaderAsset::CompileShaders()
{
	D_ASSERT(IsHasAnyValidShaderTextString() == true);
	
	for(size_t shaderStageIndex = 0 ; shaderStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT ; shaderStageIndex++)
	{
		if (mShaderTextStrings[shaderStageIndex].IsValid() == true)
		{
			const bool isSucessCompileShader = CompileSpecificTypeShader(mShaderTextStrings[shaderStageIndex], static_cast<graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderStageIndex), mShaderObject[shaderStageIndex]);
			D_ASSERT(isSucessCompileShader == true);
		}
	}
}

bool dooms::asset::ShaderAsset::CompileSpecificTypeShader(ShaderTextString& shaderText, const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType, dooms::graphics::BufferID& shaderId)
{
	D_ASSERT(shaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY);

	bool isSuccessCompileShader = false;

	if(shaderText.IsValid() == true && shaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY)
	{

		const bool isSuccessToisSuccessToConvertShaderTextStringToCurrentGraphicsAPIShaderFormat = ConvertShaderTextStringToCurrentGraphicsAPIShaderFormat(shaderText);
		D_ASSERT(isSuccessToisSuccessToConvertShaderTextStringToCurrentGraphicsAPIShaderFormat == true);
		if(isSuccessToisSuccessToConvertShaderTextStringToCurrentGraphicsAPIShaderFormat == true)
		{
			shaderId = graphics::GraphicsAPI::CreateShaderObject(shaderType);

			const char* shaderCode = shaderText.mText.c_str();
			isSuccessCompileShader = graphics::GraphicsAPI::CompileShader(shaderId.GetBufferIDRef(), shaderType, shaderCode);
			D_ASSERT_LOG(isSuccessCompileShader == true, "Fail to compile shader ( Shader Asset Name : %s, Shader Type : %s )", GetAssetFileName().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			if (isSuccessCompileShader == true)
			{
				dooms::ui::PrintText("Success to compile shader ( Shader Asset Name : %s, Shader Type : %s )", GetAssetFileName().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			}
			else
			{
				dooms::ui::PrintText("Fail to compile shader ( Shader Asset Name : %s, Shader Type : %s )", GetAssetFileName().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			}
		}
	}


	return isSuccessCompileShader;
}

void dooms::asset::ShaderAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING(Compile_Shader, eProfileLayers::Rendering);
	CompileShaders();
	D_END_PROFILING(Compile_Shader);
}

const dooms::graphics::BufferID& dooms::asset::ShaderAsset::GetShaderObject(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const
{
	D_ASSERT(targetGraphicsPipeLineStage < GRAPHICS_PIPELINE_STAGE_COUNT);

	return mShaderObject[static_cast<UINT32>(targetGraphicsPipeLineStage)];
}

bool dooms::asset::ShaderAsset::IsShaderObjectSuccessfullyCreated(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const
{
	D_ASSERT(targetGraphicsPipeLineStage < GRAPHICS_PIPELINE_STAGE_COUNT);

	return mShaderObject[static_cast<UINT32>(targetGraphicsPipeLineStage)].IsValid();
}

bool dooms::asset::ShaderAsset::IsHasAnyValidShaderObject() const
{
	bool isHasAnyValidShaderObject = false;
	for(const graphics::BufferID& shaderObject : mShaderObject)
	{
		if(shaderObject.IsValid() == true)
		{
			isHasAnyValidShaderObject = true;
			break;
		}
	}

	return isHasAnyValidShaderObject;
}

bool dooms::asset::ShaderAsset::IsHasAnyValidShaderTextString() const
{
	bool isHasAnyValidShaderTextString = false;
	for (const ShaderTextString& shaderTextStr : mShaderTextStrings)
	{
		if (shaderTextStr.IsValid() == true)
		{
			isHasAnyValidShaderTextString = true;
			break;
		}
	}

	return isHasAnyValidShaderTextString;
}

dooms::graphics::Material dooms::asset::ShaderAsset::CreateMatrialWithThisShader()
{
	return dooms::graphics::Material(this);
}

dooms::asset::eAssetType dooms::asset::ShaderAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::SHADER;
}
