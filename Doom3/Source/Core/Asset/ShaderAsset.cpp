#include <sstream>

#include "ShaderAsset.h"

#include "../Graphics/Material/Material.h"
#include "Utility/ShaderAsset/shaderAssetHelper.h"
#include <EngineGUI/PrintText.h>
#include "Utility/ShaderAsset/shaderConverter.h"
#include <Graphics/Buffer/UniformBufferObject/UniformBufferObjectManager.h>


dooms::asset::ShaderTextData::ShaderTextData() : mShaderTextGraphicsAPIType{ dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE }, mShaderStringText{}
{

}

dooms::asset::ShaderTextData::ShaderTextData
(
	const std::string& shaderStringText,
	const std::string& shaderReflectionDataStringText
)
	:
	mShaderTextGraphicsAPIType{ dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE },
	mShaderStringText{ shaderStringText },
	mShaderReflectionDataStringText(shaderReflectionDataStringText)
{

}

dooms::asset::ShaderTextData::ShaderTextData
(
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType graphicsAPIType,
	const std::string& shaderStringText,
	const std::string& shaderReflectionDataStringText
)
	:
	mShaderTextGraphicsAPIType{ graphicsAPIType },
	mShaderStringText{ shaderStringText },
	mShaderReflectionDataStringText(shaderReflectionDataStringText)
{

}

void dooms::asset::ShaderTextData::Clear()
{
	mShaderTextGraphicsAPIType = dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE;
	mShaderStringText.clear();
}

bool dooms::asset::ShaderTextData::IsValid() const
{
	return (mShaderStringText.empty() == false) && (mShaderTextGraphicsAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE);
}

dooms::asset::ShaderAsset::ShaderAsset()
	: mShaderTextDatas(), mShaderObject()
{
}


/*
dooms::asset::ShaderAsset::ShaderAsset(const std::array<ShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderTexts)
	: mShaderTextDatas(shaderTexts), mShaderObject()
{
	CompileShaders();
}
*/

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
		if(shaderObject.IsShaderObjectValid())
		{
			graphics::GraphicsAPI::DestroyShaderObject(shaderObject.mShaderObjectID);
			shaderObject.mShaderObjectID.Reset();

			shaderObject.mShaderCompileStatus = eShaderCompileStatus::READY;
		}
	}
}

void dooms::asset::ShaderAsset::ClearShaderTextStrings()
{
	for (ShaderTextData& shaderTextString : mShaderTextDatas)
	{
		shaderTextString.Clear();
	}
}


void dooms::asset::ShaderAsset::SetShaderText
(
	const std::string& shaderStringText,
	const std::string& shaderReflectionDataStringText,
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType shaderTextraphicsAPIType, 
	const bool compileShader
)
{
	D_ASSERT(shaderTextraphicsAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE);

	std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> shaderTexts = shaderAssetHelper::ParseShaderTextStringsBasedOnTargetGraphicsPipeLineStage(GetAssetPath(), shaderStringText);
	std::array<std::string, GRAPHICS_PIPELINE_STAGE_COUNT> shaderReflectionTexts = shaderAssetHelper::ParseShaderReflectionTextStringsBasedOnTargetGraphicsPipeLineStage(shaderReflectionDataStringText);
	for (size_t shaderTextIndex = 0; shaderTextIndex < GRAPHICS_PIPELINE_STAGE_COUNT; shaderTextIndex++)
	{
		mShaderTextDatas[shaderTextIndex].mShaderTextGraphicsAPIType = shaderTextraphicsAPIType;
		mShaderTextDatas[shaderTextIndex].mShaderStringText = shaderTexts[shaderTextIndex];
		mShaderTextDatas[shaderTextIndex].mShaderReflectionDataStringText = shaderReflectionTexts[shaderTextIndex];

		const bool isSuccessToisSuccessToConvertShaderTextStringToCurrentGraphicsAPIShaderFormat = ConvertShaderTextStringToCurrentGraphicsAPIShaderFormat(mShaderTextDatas[shaderTextIndex]);
		D_ASSERT(isSuccessToisSuccessToConvertShaderTextStringToCurrentGraphicsAPIShaderFormat == true);

		mShaderTextDatas[shaderTextIndex].mShaderReflectionData = dooms::asset::shaderReflectionDataParser::ParseShaderReflectionStringText(mShaderTextDatas[shaderTextIndex].mShaderReflectionDataStringText);
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

const std::string& dooms::asset::ShaderAsset::GetShaderStringText
(
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType shaderTextraphicsAPIType
) const
{
	return mShaderTextDatas[static_cast<UINT32>(shaderTextraphicsAPIType)].mShaderStringText;
}

const std::string& dooms::asset::ShaderAsset::GetShaderReflectionDataStringText
(
	const dooms::graphics::GraphicsAPI::eGraphicsAPIType shaderTextraphicsAPIType
) const
{
	return mShaderTextDatas[static_cast<UINT32>(shaderTextraphicsAPIType)].mShaderReflectionDataStringText;
}

dooms::asset::ShaderAsset::ShaderObject::ShaderObject()
	: mShaderObjectID(), mShaderCompileStatus(eShaderCompileStatus::READY)
{
}

bool dooms::asset::ShaderAsset::ShaderObject::IsShaderObjectValid() const
{
	return (mShaderObjectID.IsValid()) && (mShaderCompileStatus == eShaderCompileStatus::COMPILE_SUCCESS);
}

bool dooms::asset::ShaderAsset::ConvertShaderTextStringToCurrentGraphicsAPIShaderFormat(ShaderTextData& outShaderText)
{
	bool isConvertingSuccess = false;

	D_ASSERT(outShaderText.IsValid());
	if (outShaderText.IsValid() == true)
	{
		isConvertingSuccess = true;

		const dooms::graphics::GraphicsAPI::eGraphicsAPIType currentShaderTextGraphicsAPIType = outShaderText.mShaderTextGraphicsAPIType;
		const dooms::graphics::GraphicsAPI::eGraphicsAPIType currentLoadedGraphicsAPIType = dooms::graphics::GraphicsAPI::GetCurrentAPIType();

		if(currentShaderTextGraphicsAPIType != currentLoadedGraphicsAPIType)
		{
			std::string convertedShaderTextStr{};

			isConvertingSuccess = dooms::asset::shaderConverter::ConvertShaderTextFormat
			(
				outShaderText.mShaderStringText,
				convertedShaderTextStr,
				currentShaderTextGraphicsAPIType, 
				currentLoadedGraphicsAPIType
			);

			// TODO : Update reflection data string too.

			D_ASSERT(convertedShaderTextStr.empty() == false);
			outShaderText.mShaderStringText = std::move(convertedShaderTextStr);
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
		if (mShaderTextDatas[shaderStageIndex].IsValid() == true)
		{
			const bool isSucessCompileShader = CompileSpecificTypeShader(mShaderTextDatas[shaderStageIndex], static_cast<graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderStageIndex), mShaderObject[shaderStageIndex]);
			D_ASSERT(isSucessCompileShader == true);
		}
	}
}

bool dooms::asset::ShaderAsset::CompileSpecificTypeShader(ShaderTextData& shaderText, const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType, ShaderObject& shaderObject)
{
	D_ASSERT(shaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY);

	bool isSuccessCompileShader = false;

	if (shaderText.IsValid() == true && shaderObject.mShaderObjectID.IsValid() == false && shaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY)
	{
		shaderObject.mShaderObjectID = graphics::GraphicsAPI::CreateShaderObject(shaderType);
		if(shaderObject.mShaderObjectID.IsValid())
		{
			shaderObject.mShaderCompileStatus = eShaderCompileStatus::SHADER_OBJECT_CREATED;

			const char* shaderCode = shaderText.mShaderStringText.c_str();
			isSuccessCompileShader = graphics::GraphicsAPI::CompileShader(shaderObject.mShaderObjectID.GetBufferIDRef(), shaderType, shaderCode);
			D_ASSERT_LOG(isSuccessCompileShader == true, "Fail to compile shader ( Shader Asset Name : %s, Shader Type : %s )", GetAssetFileName().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			if (isSuccessCompileShader == true)
			{
				shaderObject.mShaderCompileStatus = eShaderCompileStatus::COMPILE_SUCCESS;
				GenerateUniformBufferObjectFromShaderReflectionData(shaderText.mShaderReflectionData);
				
				dooms::ui::PrintText("Success to compile shader ( Shader Asset Name : %s, Shader Type : %s )", GetAssetFileName().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			}
			else
			{
				shaderObject.mShaderCompileStatus = eShaderCompileStatus::COMPILE_FAIL;
				dooms::ui::PrintText("Fail to compile shader ( Shader Asset Name : %s, Shader Type : %s )", GetAssetFileName().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			}
		}
		else
		{
			shaderObject.mShaderCompileStatus = eShaderCompileStatus::COMPILE_FAIL;
		}
	}


	return isSuccessCompileShader;
}

void dooms::asset::ShaderAsset::GenerateUniformBufferObjectFromShaderReflectionData(const shaderReflectionDataParser::ShaderReflectionData& shaderReflectionData)
{
	for(const shaderReflectionDataParser::UniformBuffer& uniformBufferData : shaderReflectionData.mUniformBuffers)
	{
		dooms::graphics::UniformBufferObjectManager::GetSingleton()->GenerateUniformBufferObjectIfNotExist
		(
			uniformBufferData.mName,
			uniformBufferData.mSize,
			uniformBufferData.mBindingPoint,
			nullptr,
			&(uniformBufferData.mMembers)
		);
	}
	
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

	return mShaderObject[static_cast<UINT32>(targetGraphicsPipeLineStage)].mShaderObjectID;
}

bool dooms::asset::ShaderAsset::IsShaderObjectSuccessfullyCreated(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const
{
	D_ASSERT(targetGraphicsPipeLineStage < GRAPHICS_PIPELINE_STAGE_COUNT);

	return mShaderObject[static_cast<UINT32>(targetGraphicsPipeLineStage)].mShaderObjectID;
}

bool dooms::asset::ShaderAsset::IsHasAnyValidShaderObject() const
{
	bool isHasAnyValidShaderObject = false;
	for(const ShaderObject& shaderObject : mShaderObject)
	{
		if(shaderObject.IsShaderObjectValid() == true)
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
	for (const ShaderTextData& shaderTextStr : mShaderTextDatas)
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
	CompileShaderIfNotCompiled();

	D_ASSERT(IsHasAnyValidShaderObject() == true);
	return dooms::graphics::Material(this);
}

void dooms::asset::ShaderAsset::CompileShaderIfNotCompiled()
{
	if (IsHasAnyValidShaderObject() == false)
	{
		CompileShaders();
	}
}

dooms::asset::eAssetType dooms::asset::ShaderAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::SHADER;
}
