#include <sstream>

#include "ShaderAsset.h"

#include <algorithm>
#include <d3d11.h>

#include "../Graphics/Material/Material.h"
#include "Utility/ShaderAsset/shaderAssetHelper.h"
#include <EngineGUI/PrintText.h>
#include "Utility/ShaderAsset/shaderConverter.h"
#include <Graphics/Buffer/UniformBufferObject/UniformBufferObjectManager.h>


dooms::asset::ShaderTextData::ShaderTextData()
	:
	mShaderTextGraphicsAPIType{ dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE },
	mShaderStringText{},
	mShaderReflectionData{}
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
	mShaderReflectionDataStringText(shaderReflectionDataStringText),
	mShaderReflectionData{}
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
	mShaderReflectionDataStringText(shaderReflectionDataStringText),
	mShaderReflectionData{}
{

}

void dooms::asset::ShaderTextData::Clear()
{
	mShaderTextGraphicsAPIType = dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE;
	mShaderStringText.clear();
	mShaderReflectionDataStringText.clear();
	mShaderReflectionData.Clear();
}

bool dooms::asset::ShaderTextData::IsCompileliable() const
{
	return	(mShaderStringText.empty() == false) &&
			(mShaderTextGraphicsAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE) &&
			(mShaderReflectionData.mIsGenerated == true);
}


bool dooms::asset::ShaderTextData::LoadShaderReflectionDataFromTextIfNotLoaded()
{
	bool isLoaded = false;

	if( (mShaderReflectionDataStringText.empty() == false) && (mShaderReflectionData.mIsGenerated == false) )
	{
		mShaderReflectionData = dooms::asset::shaderReflectionDataParser::ParseShaderReflectionStringText(mShaderReflectionDataStringText);
		isLoaded = mShaderReflectionData.mIsGenerated;
	}

	return isLoaded;
}

dooms::asset::ShaderAsset::ShaderAsset()
	: mShaderTextDatas(), mShaderObject(), mInputLayoutForD3D()
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
	ClearShaderTextDatas();
}

void dooms::asset::ShaderAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();
	
	DestroyShaderObjects();
	ClearShaderTextDatas();
}

const std::vector<dooms::graphics::UniformBufferObject*>& dooms::asset::ShaderAsset::GetContainedUniformBufferObject() const
{
	return mContainedUniformBufferObjects;
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
	mContainedUniformBufferObjects.clear();

	if (mInputLayoutForD3D.IsValid())
	{
		dooms::graphics::GraphicsAPI::DestoryInputLayoutForD3D(mInputLayoutForD3D);
		mInputLayoutForD3D.Reset();
	}
}

void dooms::asset::ShaderAsset::ClearShaderTextDatas()
{
	for (ShaderTextData& shaderTextString : mShaderTextDatas)
	{
		shaderTextString.Clear();
	}
}

bool dooms::asset::ShaderAsset::SetShaderText
(
	const std::array<ShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderTextDatas,
	const bool compileShader
)
{
	bool isSuccess = true;

	ClearShaderTextDatas();

	mShaderTextDatas = shaderTextDatas;

	for(ShaderTextData& shaderTextData : mShaderTextDatas)
	{
		if
		(
			(shaderTextData.mShaderStringText.empty() == false) &&
			(shaderTextData.mShaderTextGraphicsAPIType != dooms::graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE)
		)
		{
			if (shaderTextData.mShaderReflectionDataStringText.empty() == false)
			{
				shaderTextData.LoadShaderReflectionDataFromTextIfNotLoaded();
			}

			D_ASSERT(shaderTextData.mShaderReflectionData.mTargetGraphicsAPIType == dooms::graphics::GraphicsAPI::GetCurrentAPIType());
		}
	}

	D_ASSERT_LOG
	(
		IsHasAnyValidShaderTextString() == true,
		"Shader Asset doesn't have any shader string ( File Path : %s )", GetAssetPathAsUTF8Str().c_str()
	);
	if (IsHasAnyValidShaderTextString() == false)
	{
		isSuccess = false;
		dooms::ui::PrintText("Shader Asset doesn't have any shader string ( File Path : %s )", GetAssetPathAsUTF8Str().c_str());
	}

	if (compileShader == true)
	{
		isSuccess &= CompileShaders();
	}

	return isSuccess;
}


/*
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

		if(mShaderTextDatas[shaderTextIndex].mShaderReflectionData.mIsGenerated == false)
		{
			mShaderTextDatas[shaderTextIndex].mShaderReflectionData = dooms::asset::shaderReflectionDataParser::ParseShaderReflectionStringText(mShaderTextDatas[shaderTextIndex].mShaderReflectionDataStringText);
		}
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
*/

const std::string& dooms::asset::ShaderAsset::GetShaderStringText
(
	const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage
) const
{
	return mShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].mShaderStringText;
}

const std::string& dooms::asset::ShaderAsset::GetShaderReflectionDataStringText
(
	const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage
) const
{
	return mShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].mShaderReflectionDataStringText;
}

const dooms::asset::shaderReflectionDataParser::ShaderReflectionData& dooms::asset::ShaderAsset::GetShaderReflectionData
(
	const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage
) const
{
	D_ASSERT(mShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].mShaderReflectionData.mIsGenerated == true);
	return mShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].mShaderReflectionData;
}

dooms::asset::ShaderAsset::ShaderObject::ShaderObject()
	: mShaderObjectID(), mShaderCompileStatus(eShaderCompileStatus::READY)
{
}

bool dooms::asset::ShaderAsset::ShaderObject::IsShaderObjectValid() const
{
	return (mShaderObjectID.IsValid()) && (mShaderCompileStatus == eShaderCompileStatus::COMPILE_SUCCESS);
}

/*
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
*/

bool dooms::asset::ShaderAsset::CompileShaders()
{
	D_ASSERT(IsHasAnyValidShaderTextString() == true);

	bool isSuccess = true;

	for(size_t shaderStageIndex = 0 ; shaderStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT ; shaderStageIndex++)
	{
		if (mShaderTextDatas[shaderStageIndex].IsCompileliable() == true)
		{
			const bool isSucessCompileShader = CompileSpecificTypeShader(mShaderTextDatas[shaderStageIndex], static_cast<graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderStageIndex), mShaderObject[shaderStageIndex]);
			D_ASSERT(isSucessCompileShader == true);

			isSuccess &= isSucessCompileShader;
		}
	}

	return isSuccess;
}

bool dooms::asset::ShaderAsset::CompileSpecificTypeShader(ShaderTextData& shaderText, const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType, ShaderObject& shaderObject)
{
	D_ASSERT(shaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY);

	bool isSuccessCompileShader = false;

	D_ASSERT(shaderText.IsCompileliable() == true);
	D_ASSERT(shaderObject.mShaderObjectID.IsValid() == false);
	if (shaderText.IsCompileliable() == true && shaderObject.mShaderObjectID.IsValid() == false && shaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY)
	{
		if(dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			shaderObject.mShaderObjectID = graphics::GraphicsAPI::CreateShaderObject(shaderType);
		}

		D_ASSERT
		(
			shaderObject.mShaderObjectID.IsValid() ||
			(dooms::graphics::GraphicsAPI::GetCurrentAPIType() != dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		);
		if
		(
			shaderObject.mShaderObjectID.IsValid() ||
			(dooms::graphics::GraphicsAPI::GetCurrentAPIType() != dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		)
		{
			shaderObject.mShaderCompileStatus = eShaderCompileStatus::SHADER_OBJECT_CREATED;

			const char* shaderCode = shaderText.mShaderStringText.c_str();
			isSuccessCompileShader = graphics::GraphicsAPI::CompileShader(shaderObject.mShaderObjectID.GetBufferIDRef(), shaderType, shaderCode, shaderText.mShaderStringText.size());
			D_ASSERT_LOG(isSuccessCompileShader == true, "Fail to compile shader ( Shader Asset Name : %s, Shader Type : %s )", shaderText.mShaderTextFilePath.generic_u8string().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			if (isSuccessCompileShader == true)
			{
				shaderObject.mShaderCompileStatus = eShaderCompileStatus::COMPILE_SUCCESS;
				GenerateUniformBufferObjectFromShaderReflectionData(shaderText.mShaderReflectionData);

				if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
				{
					if (shaderType == graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER)
					{
						CreateInputLayoutForD3D(this);
					}
				}
				dooms::ui::PrintText("Success to compile shader ( Shader Asset Name : %s, Shader Type : %s )", shaderText.mShaderTextFilePath.generic_u8string().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			}
			else
			{
				shaderObject.mShaderCompileStatus = eShaderCompileStatus::COMPILE_FAIL;
				dooms::ui::PrintText("Fail to compile shader ( Shader Asset Name : %s, Shader Type : %s )", shaderText.mShaderTextFilePath.generic_u8string().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(shaderType)]);
			}
		}
		else
		{
			shaderObject.mShaderCompileStatus = eShaderCompileStatus::COMPILE_FAIL;
		}
	}


	return isSuccessCompileShader;
}

const std::vector<dooms::graphics::UniformBufferObject*>& dooms::asset::ShaderAsset::GenerateUniformBufferObjectFromShaderReflectionData(const shaderReflectionDataParser::ShaderReflectionData& shaderReflectionData)
{
	for(const shaderReflectionDataParser::UniformBuffer& uniformBufferData : shaderReflectionData.mUniformBuffers)
	{
		const unsigned long long alignedSize = uniformBufferData.mBlockSize + ((uniformBufferData.mBlockSize % 16) == 0 ? 0 : (16 - (uniformBufferData.mBlockSize % 16)));
		//D3D11 require constant buffer size to be multiple of 16

		dooms::graphics::UniformBufferObject* const ubo = dooms::graphics::UniformBufferObjectManager::GetSingleton()->GetOrGenerateUniformBufferObjectIfNotExist
		(
			uniformBufferData.mName,
			alignedSize,
			uniformBufferData.mBindingPoint,
			nullptr,
			&(uniformBufferData.mMembers)
		);
		D_ASSERT(IsValid(ubo));
		if(IsValid(ubo))
		{
			if(std::find(mContainedUniformBufferObjects.begin(), mContainedUniformBufferObjects.end(), ubo) == mContainedUniformBufferObjects.end())
			{
				mContainedUniformBufferObjects.push_back(ubo);
			}
			
		}
	}

	return mContainedUniformBufferObjects;
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
		if (shaderTextStr.IsCompileliable() == true)
		{
			isHasAnyValidShaderTextString = true;
			break;
		}
	}

	return isHasAnyValidShaderTextString;
}


namespace dooms::graphics::dx11
{
	DXGI_FORMAT Conver_From_eShaderVariableType_To_DXGI_FORMAT(const asset::shaderReflectionDataParser::eShaderVariableType shaderVariableType)
	{
		switch (shaderVariableType)
		{
		case asset::shaderReflectionDataParser::eShaderVariableType::FLOAT1:
			return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
		case asset::shaderReflectionDataParser::eShaderVariableType::FLOAT2:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
		case asset::shaderReflectionDataParser::eShaderVariableType::FLOAT3:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
		case asset::shaderReflectionDataParser::eShaderVariableType::FLOAT4:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
		case asset::shaderReflectionDataParser::eShaderVariableType::INT1:
			return DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
		case asset::shaderReflectionDataParser::eShaderVariableType::INT2:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
		case asset::shaderReflectionDataParser::eShaderVariableType::INT3:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
		case asset::shaderReflectionDataParser::eShaderVariableType::INT4:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
		case asset::shaderReflectionDataParser::eShaderVariableType::UINT1:
			return DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
		case asset::shaderReflectionDataParser::eShaderVariableType::UINT2:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT;
		case asset::shaderReflectionDataParser::eShaderVariableType::UINT3:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT;
		case asset::shaderReflectionDataParser::eShaderVariableType::UINT4:
			return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;
		default:
			D_ASSERT(false);
		}
	}
}


void dooms::asset::ShaderAsset::CreateInputLayoutForD3D(dooms::asset::ShaderAsset* const shaderAsset)
{
	if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		D_ASSERT(mInputLayoutForD3D.IsValid() == false);
		D_ASSERT(graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10);
		D_ASSERT(shaderAsset->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER) == true);
		if
			(
				mInputLayoutForD3D.IsValid() == false &&
				shaderAsset->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER) == true
				)
		{
			const dooms::asset::shaderReflectionDataParser::ShaderReflectionData& vertexShaderReflectionData = shaderAsset->GetShaderReflectionData(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER);

			D3D11_INPUT_ELEMENT_DESC layout[15];

			for (const asset::shaderReflectionDataParser::ShaderInputType& input : vertexShaderReflectionData.mInputVariables)
			{
				layout[input.mLocation].SemanticName = input.mSemanticType.c_str();
				layout[input.mLocation].SemanticIndex = input.mSemanticIndex;
				layout[input.mLocation].Format = graphics::dx11::Conver_From_eShaderVariableType_To_DXGI_FORMAT(input.mType);
				layout[input.mLocation].InputSlot = 0; //input.mLocation;
				layout[input.mLocation].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; // direct x choose offset itself
				layout[input.mLocation].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				layout[input.mLocation].InstanceDataStepRate = 0;
			}

			mInputLayoutForD3D = dooms::graphics::GraphicsAPI::CreateInputLayoutForD3D
			(
				layout,
				vertexShaderReflectionData.mInputVariables.size(),
				GetShaderObject(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER)
			);
			D_ASSERT(mInputLayoutForD3D.IsValid());
		}
	}
}


dooms::graphics::Material* dooms::asset::ShaderAsset::CreateMatrialWithThisShaderAsset()
{
	CompileShaderIfNotCompiled();

	D_ASSERT(IsHasAnyValidShaderObject() == true);

	std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT> shaderAssets;
	for(size_t shaderTypeIndex = 0 ; shaderTypeIndex < GRAPHICS_PIPELINE_STAGE_COUNT ; shaderTypeIndex++)
	{
		if(IsShaderObjectSuccessfullyCreated(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderTypeIndex)))
		{
			shaderAssets[shaderTypeIndex] = this;
		}
		else
		{
			shaderAssets[shaderTypeIndex] = nullptr;
		}
	}

	dooms::graphics::Material* const material = dooms::CreateDObject<dooms::graphics::Material>(shaderAssets);
	D_ASSERT(IsValid(material) == true);

	return material;
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

dooms::asset::ShaderAsset::eShaderCompileStatus dooms::asset::ShaderAsset::GetCurrentShaderCompileStatus
(
	const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType
) const
{
	return mShaderObject[shaderType].mShaderCompileStatus;
}
