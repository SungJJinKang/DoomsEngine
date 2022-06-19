#include "RenderingShaderProxy.h"

#include <d3d11.h>
#include <dxgiformat.h>

#include "EngineGUI/PrintText.h"
#include "Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h"

dooms::graphics::RenderingShaderProxy::~RenderingShaderProxy()
{
	DestroyShaderObjects();
}

void dooms::graphics::RenderingShaderProxy::InitRenderingShaderProxy(FRenderingShaderProxyInitializer& Initilizer)
{
	ShaderTextDatas = std::move(Initilizer.ShaderTextDatas);
	ContainedRenderingUniformBufferProxyList = std::move(Initilizer.RenderingUniformBufferProxyList);
}

bool dooms::graphics::RenderingShaderProxy::CompileShaders()
{
	D_ASSERT(IsHasAnyValidShaderTextString() == true);

	bool isSuccess = true;

	for (size_t shaderStageIndex = 0; shaderStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; shaderStageIndex++)
	{
		if (ShaderTextDatas[shaderStageIndex].IsCompileliable() == true)
		{
			const bool isSucessCompileShader = CompileSpecificTypeShader
												(ShaderTextDatas[shaderStageIndex], 
													static_cast<graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderStageIndex), 
													ShaderObjects[shaderStageIndex]
												);
			D_ASSERT(isSucessCompileShader == true);

			isSuccess &= isSucessCompileShader;
		}
	}

	return isSuccess;
}

void dooms::graphics::RenderingShaderProxy::DestroyShaderObjects()
{
	for (FShaderObject& ShaderObject : ShaderObjects)
	{
		if (ShaderObject.IsShaderObjectValid())
		{
			graphics::GraphicsAPI::DestroyShaderObject(ShaderObject.ShaderObjectID);
			ShaderObject.ShaderObjectID.Reset();

			ShaderObject.ShaderCompileStatus = eShaderCompileStatus::READY;
		}
	}
	
	ContainedRenderingUniformBufferProxyList.clear();

	if (InputLayoutForD3D.IsValid())
	{
		dooms::graphics::GraphicsAPI::DestoryInputLayoutForD3D(InputLayoutForD3D);
		InputLayoutForD3D.Reset();
	}
}

dooms::graphics::BufferID dooms::graphics::RenderingShaderProxy::GetShaderObject(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const
{
	D_ASSERT(targetGraphicsPipeLineStage < GRAPHICS_PIPELINE_STAGE_COUNT);

	return ShaderObjects[static_cast<UINT32>(targetGraphicsPipeLineStage)].ShaderObjectID;
}

dooms::graphics::eShaderCompileStatus dooms::graphics::RenderingShaderProxy::GetCurrentShaderCompileStatus(const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType) const
{
	return ShaderObjects[shaderType].ShaderCompileStatus;
}

bool dooms::graphics::RenderingShaderProxy::IsHasAnyValidShaderObject() const
{
	bool isHasAnyValidShaderObject = false;
	for (const FShaderObject& ShaderObject : ShaderObjects)
	{
		if (ShaderObject.IsShaderObjectValid() == true)
		{
			isHasAnyValidShaderObject = true;
			break;
		}
	}

	return isHasAnyValidShaderObject;
}

bool dooms::graphics::RenderingShaderProxy::IsShaderObjectSuccessfullyCreated(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage TargetGraphicsPipeLineStage) const
{
	D_ASSERT(TargetGraphicsPipeLineStage < GRAPHICS_PIPELINE_STAGE_COUNT);

	return ShaderObjects[static_cast<UINT32>(TargetGraphicsPipeLineStage)].ShaderObjectID;
}

bool dooms::graphics::RenderingShaderProxy::IsHasAnyValidShaderTextString() const
{
	bool isHasAnyValidShaderTextString = false;
	for (const asset::FShaderTextData& ShaderTextStr : ShaderTextDatas)
	{
		if (ShaderTextStr.IsCompileliable() == true)
		{
			isHasAnyValidShaderTextString = true;
			break;
		}
	}

	return isHasAnyValidShaderTextString;
}

const dooms::asset::shaderReflectionDataParser::ShaderReflectionData& dooms::graphics::RenderingShaderProxy::GetShaderReflectionData(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const
{
	return ShaderTextDatas[static_cast<UINT32>(targetGraphicsPipeLineStage)].ShaderReflectionData;
}

const std::vector<dooms::graphics::RenderingUniformBufferProxy*>& dooms::graphics::RenderingShaderProxy::GetContainedRenderingUniformBufferProxyList() const
{
	return ContainedRenderingUniformBufferProxyList;
}

dooms::graphics::RenderingShaderProxy::FShaderObject::FShaderObject()
	: ShaderObjectID(), ShaderCompileStatus(eShaderCompileStatus::READY)
{
}

bool dooms::graphics::RenderingShaderProxy::FShaderObject::IsShaderObjectValid() const
{
	return (ShaderObjectID.IsValid()) && (ShaderCompileStatus == eShaderCompileStatus::COMPILE_SUCCESS);
}

bool dooms::graphics::RenderingShaderProxy::CompileSpecificTypeShader(asset::FShaderTextData& ShaderText, const graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType, FShaderObject& ShaderObject)
{
	D_ASSERT(ShaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY);

	bool bIsSuccessCompileShader = false;

	D_ASSERT(ShaderText.IsCompileliable() == true);
	D_ASSERT(ShaderObject.ShaderObjectID.IsValid() == false);
	if (ShaderText.IsCompileliable() == true && ShaderObject.ShaderObjectID.IsValid() == false && ShaderType != graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY)
	{
		if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			ShaderObject.ShaderObjectID = graphics::GraphicsAPI::CreateShaderObject(ShaderType);
		}

		D_ASSERT
		(
			ShaderObject.ShaderObjectID.IsValid() ||
			(dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() != dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		);
		if
			(
				ShaderObject.ShaderObjectID.IsValid() ||
				(dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() != dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
				)
		{
			ShaderObject.ShaderCompileStatus = eShaderCompileStatus::SHADER_OBJECT_CREATED;

			const char* shaderCode = ShaderText.ShaderStringText.c_str();
			bIsSuccessCompileShader = graphics::GraphicsAPI::CompileShader(ShaderObject.ShaderObjectID.GetBufferIDRef(), ShaderType, shaderCode, ShaderText.ShaderStringText.size());
			D_ASSERT_LOG(bIsSuccessCompileShader == true, "Fail to compile shader ( Shader Asset Name : %s, Shader Type : %s )", ShaderText.mShaderTextFilePath.generic_u8string().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(ShaderType)]);
			if (bIsSuccessCompileShader == true)
			{
				ShaderObject.ShaderCompileStatus = eShaderCompileStatus::COMPILE_SUCCESS;

				if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
				{
					if (ShaderType == graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER)
					{
						CreateInputLayoutForD3D();
					}
				}
				dooms::ui::PrintText("Success to compile shader ( Shader Asset Name : %s, Shader Type : %s )", ShaderText.mShaderTextFilePath.generic_u8string().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(ShaderType)]);
			}
			else
			{
				ShaderObject.ShaderCompileStatus = eShaderCompileStatus::COMPILE_FAIL;
				dooms::ui::PrintText("Fail to compile shader ( Shader Asset Name : %s, Shader Type : %s )", ShaderText.mShaderTextFilePath.generic_u8string().c_str(), graphics::GraphicsAPI::eGraphicsPipeLineStageString[static_cast<UINT32>(ShaderType)]);
			}
		}
		else
		{
			ShaderObject.ShaderCompileStatus = eShaderCompileStatus::COMPILE_FAIL;
		}
	}


	return bIsSuccessCompileShader;
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
			NEVER_HAPPEN;
		}
	}
}



void dooms::graphics::RenderingShaderProxy::CreateInputLayoutForD3D()
{
	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		D_ASSERT(InputLayoutForD3D.IsValid() == false);
		D_ASSERT(graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10);
		D_ASSERT(IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER) == true);
		if
		(
			InputLayoutForD3D.IsValid() == false &&
			IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER) == true
		)
		{
			const dooms::asset::shaderReflectionDataParser::ShaderReflectionData& vertexShaderReflectionData = GetShaderReflectionData(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER);

			D3D11_INPUT_ELEMENT_DESC layout[15];

			for (const asset::shaderReflectionDataParser::ShaderInputType& input : vertexShaderReflectionData.mInputVariables)
			{
				layout[input.mLocation].SemanticName = input.mSemanticType.c_str();
				layout[input.mLocation].SemanticIndex = input.mSemanticIndex;
				layout[input.mLocation].Format = graphics::dx11::Conver_From_eShaderVariableType_To_DXGI_FORMAT(input.mType);
				layout[input.mLocation].InputSlot = input.mLocation;
				layout[input.mLocation].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; // direct x choose offset itself
				layout[input.mLocation].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				layout[input.mLocation].InstanceDataStepRate = 0;
			}

			InputLayoutForD3D = dooms::graphics::GraphicsAPI::CreateInputLayoutForD3D
			(
				layout,
				vertexShaderReflectionData.mInputVariables.size(),
				GetShaderObject(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER)
			);
			D_ASSERT(InputLayoutForD3D.IsValid());
		}
	}
}
