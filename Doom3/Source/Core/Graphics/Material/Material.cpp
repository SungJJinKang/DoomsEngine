#include "Material.h"

#include <Asset/ShaderAsset.h>

#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include "FixedMaterial.h"
#include "../Buffer/UniformBufferObject/UniformBufferObjectManager.h"
#include <Asset/TextureAsset.h>
#include "../Texture/TextureView.h"

#include <d3d11.h>
#include <dxgiformat.h>

bool dooms::graphics::Material::AttachShaderToMaterial(dooms::asset::ShaderAsset* const shaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
{
	D_ASSERT(IsValid(shaderAsset));
	D_ASSERT(shaderAsset->GetShaderObject(shaderType).IsValid());

	bool isSuccess = true;

	if (IsValid(shaderAsset) && (shaderType != dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY))
	{
		CreateMaterialObjectIfNotExist();

		shaderAsset->CompileShaderIfNotCompiled();
		
		if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			if (mProgramIDForOpenGL.IsValid())
			{
				if (shaderAsset->IsShaderObjectSuccessfullyCreated(shaderType))
				{
					DestroyShaderFromMaterial(shaderType);

					isSuccess &= GraphicsAPI::AttachShaderToMaterial(mPipeLineShaderView[shaderType].GetBufferIDRef(), mProgramIDForOpenGL.GetBufferIDRef(), shaderAsset->GetShaderObject(shaderType), shaderType);
					D_ASSERT(isSuccess == true);

					if(isSuccess == true)
					{
						const bool isSuccessLinkMaterial = GraphicsAPI::LinkMaterial(mProgramIDForOpenGL);
						D_ASSERT(isSuccessLinkMaterial == true);

						isSuccess &= isSuccessLinkMaterial;
					}
				}
			}
			else
			{
				isSuccess = false;
			}
		}
		else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			if (shaderAsset->IsShaderObjectSuccessfullyCreated(shaderType))
			{
				DestroyShaderFromMaterial(shaderType);
				isSuccess &= GraphicsAPI::AttachShaderToMaterial(mPipeLineShaderView[shaderType].GetBufferIDRef(), mProgramIDForOpenGL.GetBufferIDRef(), shaderAsset->GetShaderObject(shaderType), shaderType);
				if(shaderType == graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER)
				{
					CreateInputLayoutForD3D(shaderAsset);
				}

				D_ASSERT(isSuccess == true);
			}
		}
	}
	else
	{
		isSuccess = false;
	}

	if (isSuccess == true)
	{
		mShaderAsset[shaderType] = shaderAsset;

		const std::vector<dooms::graphics::UniformBufferObject*>& containedUBO = shaderAsset->GetContainedUniformBufferObject();
		for(dooms::graphics::UniformBufferObject* ubo : containedUBO)
		{
			AddUniformBufferObjectView(ubo, shaderType);
		}

		mMaterialStatus = eStatus::SUCCESS;
	}
	else
	{
		mMaterialStatus = eStatus::FAIL;
	}

	D_ASSERT(isSuccess == true);
	return isSuccess;
}

void dooms::graphics::Material::SetShaderAsset(dooms::asset::ShaderAsset* const shaderAsset)
{
	D_ASSERT(IsValid(shaderAsset));
	for (size_t shaderTypeIndex = 0; shaderTypeIndex < GRAPHICS_PIPELINE_STAGE_COUNT; shaderTypeIndex++)
	{
		if(shaderAsset->IsShaderObjectSuccessfullyCreated(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderTypeIndex)))
		{
			SetShaderAsset(shaderAsset, static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderTypeIndex));
		}
	}
}

void dooms::graphics::Material::SetShaderAsset(dooms::asset::ShaderAsset* const shaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
{
	D_ASSERT(IsValid(shaderAsset) == true);
	D_ASSERT(shaderAsset->IsShaderObjectSuccessfullyCreated(shaderType));
	
	AttachShaderToMaterial(shaderAsset, shaderType);
}

void dooms::graphics::Material::SetShaderAsset(const std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderAssets)
{
	mTargetUniformBufferObjectViews.clear();
	for(size_t shaderTypeIndex = 0 ; shaderTypeIndex < GRAPHICS_PIPELINE_STAGE_COUNT ; shaderTypeIndex++)
	{
		SetShaderAsset(shaderAssets[shaderTypeIndex], static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderTypeIndex));
	}
}

bool dooms::graphics::Material::IsHasAnyValidShaderObject() const
{
	bool isHasAnyValidShaderObject = false;

	if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (mProgramIDForOpenGL.IsValid())
		{
			isHasAnyValidShaderObject = true;
		}
	}
	else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
		{
			if (mPipeLineShaderView[pipeLineStageIndex].IsValid() == true)
			{
				isHasAnyValidShaderObject = true;
				break;
			}
		}
	}

	return isHasAnyValidShaderObject;
}


dooms::graphics::Material::Material()
	:
	mMaterialStatus(eStatus::READY),
	mProgramIDForOpenGL{ },
	mShaderAsset{ nullptr },
	mPipeLineShaderView{},
	mTargetUniformBufferObjectViews{},
	mInputLayoutForD3D()
{

}

dooms::graphics::Material::Material(dooms::asset::ShaderAsset* const shaderAsset)
	:
	mMaterialStatus(eStatus::READY),
	mProgramIDForOpenGL{},
	mShaderAsset{ nullptr },
	mPipeLineShaderView{},
	mTargetUniformBufferObjectViews{},
	mInputLayoutForD3D()
{
	D_ASSERT(IsValid(shaderAsset));
	SetShaderAsset(shaderAsset);
}

dooms::graphics::Material::Material(dooms::asset::ShaderAsset* const shaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
	:
	mMaterialStatus(eStatus::READY),
	mProgramIDForOpenGL{},
	mShaderAsset{ nullptr },
	mPipeLineShaderView{},
	mTargetUniformBufferObjectViews{},
	mInputLayoutForD3D()
{
	if (IsValid(shaderAsset) == true)
	{
		SetShaderAsset(shaderAsset, shaderType);
	}
}

dooms::graphics::Material::Material(const std::array<dooms::asset::ShaderAsset*, GRAPHICS_PIPELINE_STAGE_COUNT>& shaderAssets)
	:
	mMaterialStatus(eStatus::READY),
	mProgramIDForOpenGL{},
	mShaderAsset{ nullptr },
	mPipeLineShaderView{},
	mTargetUniformBufferObjectViews{},
	mInputLayoutForD3D()
{
	SetShaderAsset(shaderAssets);
}

void dooms::graphics::Material::CreateMaterialObjectIfNotExist()
{
	if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (mProgramIDForOpenGL.IsValid() == false)
		{
			mProgramIDForOpenGL = GraphicsAPI::CreateMaterial();
			D_ASSERT(mProgramIDForOpenGL.IsValid() == true);
		}
	}
	mMaterialStatus = eStatus::READY;
}

void dooms::graphics::Material::DestroyMaterialObjectIfExist()
{
	if(dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (mProgramIDForOpenGL.IsValid())
		{
			GraphicsAPI::DestroyMaterial(mProgramIDForOpenGL);
			mProgramIDForOpenGL.Reset();
		}
	}
	else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
		{
			DestroyShaderFromMaterial(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex));
		}

		if(mInputLayoutForD3D.IsValid())
		{
			dooms::graphics::GraphicsAPI::DestoryInputLayoutForD3D(mInputLayoutForD3D);
			mInputLayoutForD3D.Reset();
		}
	}

	mTargetUniformBufferObjectViews.clear();

	mMaterialStatus = eStatus::READY;
}

void dooms::graphics::Material::DestroyShaderFromMaterial(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
{
	if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (mProgramIDForOpenGL.IsValid() && IsValid(mShaderAsset[shaderType]) && mShaderAsset[shaderType]->GetShaderObject(shaderType).IsValid())
		{
			GraphicsAPI::DetachShaderFromMaterial(mPipeLineShaderView[shaderType], mProgramIDForOpenGL, mShaderAsset[shaderType]->GetShaderObject(shaderType));
		}
	}
	else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		if(mPipeLineShaderView[shaderType].IsValid())
		{
			GraphicsAPI::DetachShaderFromMaterial(mPipeLineShaderView[shaderType], mProgramIDForOpenGL, mShaderAsset[shaderType]->GetShaderObject(shaderType));
			mPipeLineShaderView[shaderType].Reset();
		}		
	}
}


void dooms::graphics::Material::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestroyMaterialObjectIfExist();
}

dooms::graphics::UniformBufferObjectView* dooms::graphics::Material::AddUniformBufferObjectView
(
	UniformBufferObject* const ubo,
	const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
)
{
	D_ASSERT(IsValid(ubo));

	UniformBufferObjectView* addedUbo = nullptr;

	if(IsValid(ubo))
	{
		if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			// In opengl, Uniform Buffer Object is bound one time regardless of target graphics pipe line stage
			for(UniformBufferObjectView& uboView : mTargetUniformBufferObjectViews)
			{
				if(uboView.GetTargetUniformBufferObject() == ubo)
				{
					addedUbo = &uboView;
					break;
				}
			}
			
			if (addedUbo == nullptr)
			{
				UniformBufferObjectView& uboView = mTargetUniformBufferObjectViews.emplace_back
				(
					this,
					ubo,
					ubo->GetDefaultBindingPoint(),
					targetPipeLineStage
				);
				addedUbo = &uboView;
			}
		}
		else if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			// In direct x, Constant Buffer should be bound to target graphics pipe line stage.
			UniformBufferObjectView& uboView = mTargetUniformBufferObjectViews.emplace_back
			(
				this,
				ubo,
				ubo->GetDefaultBindingPoint(),
				targetPipeLineStage
			);
			addedUbo = &uboView;
		}
		else
		{
			D_ASSERT(false);
		}
	}
	
	
	
	D_ASSERT(IsValid(addedUbo));

	return addedUbo;
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

void dooms::graphics::Material::CreateInputLayoutForD3D(dooms::asset::ShaderAsset* const vertexShaderAsset)
{
	D_ASSERT(mInputLayoutForD3D.IsValid() == false);
	D_ASSERT(graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10);
	D_ASSERT(vertexShaderAsset->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER) == true);
	if
	(
		mInputLayoutForD3D.IsValid() == false &&
		vertexShaderAsset->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER) == true
	)
	{
		const dooms::asset::shaderReflectionDataParser::ShaderReflectionData& vertexShaderReflectionData = vertexShaderAsset->GetShaderReflectionData(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER);

		D3D11_INPUT_ELEMENT_DESC layout[15];

		for(const asset::shaderReflectionDataParser::ShaderInputType& input : vertexShaderReflectionData.mInputVariables)
		{
			layout[input.mLocation].SemanticName = input.mSemanticType.c_str();
			layout[input.mLocation].SemanticIndex = input.mSemanticIndex;
			layout[input.mLocation].Format = dx11::Conver_From_eShaderVariableType_To_DXGI_FORMAT(input.mType);
			layout[input.mLocation].InputSlot = input.mLocation;
			layout[input.mLocation].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; // direct x choose offset itself
			layout[input.mLocation].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			layout[input.mLocation].InstanceDataStepRate = 0;
		}

		

		mInputLayoutForD3D = dooms::graphics::GraphicsAPI::CreateInputLayoutForD3D
		(
			layout,
			vertexShaderReflectionData.mInputVariables.size(),
			vertexShaderAsset->GetShaderObject(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER)
		);
		D_ASSERT(mInputLayoutForD3D.IsValid());
	}
}


dooms::graphics::Material::~Material()
{
	DestroyMaterialObjectIfExist();
}


void dooms::graphics::Material::AddTexture(UINT32 bindingPoint, TextureView* texture)
{
	D_ASSERT(IsHasAnyValidShaderObject() == true);
	mTargetTextures[bindingPoint] = texture;
}

void dooms::graphics::Material::AddTexture(const UINT32 bindingPoint, const dooms::asset::TextureAsset* const textureAsset)
{
	D_ASSERT(IsHasAnyValidShaderObject() == true);
	mTargetTextures.push_back(textureAsset->GenerateTextureView(bindingPoint, GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
}

void dooms::graphics::Material::AddTextures(const std::vector<const TextureView*>& textures)
{
	D_ASSERT(IsHasAnyValidShaderObject() == true);
	mTargetTextures = textures;
}

void dooms::graphics::Material::BindMaterial() const
{
	if (FixedMaterial::GetIsFixedMaterialExist() == false)
	{

		if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
			{
				if (mPipeLineShaderView[pipeLineStageIndex].IsValid() == true)
				{
					GraphicsAPI::BindShader(mPipeLineShaderView[pipeLineStageIndex], (static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)));
				}
			}

			D_ASSERT(mInputLayoutForD3D.IsValid());
			if (mInputLayoutForD3D.IsValid())
			{
				GraphicsAPI::BindInputLayoutForD3D(mInputLayoutForD3D);
			}
		}
		else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(MATERIAL_TAG, mProgramIDForOpenGL))
			{
				D_ASSERT(mProgramIDForOpenGL.IsValid());
				if (mProgramIDForOpenGL.IsValid() == true)
				{
					GraphicsAPI::BindShader(mProgramIDForOpenGL, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
				}
			}
		}

		for (UINT32 i = 0; i < mTargetTextures.size(); i++)
		{
			if (IsValid(mTargetTextures[i]) == true)
			{
				mTargetTextures[i]->BindTexture();
			}
		}

		for (const UniformBufferObjectView& uboView : mTargetUniformBufferObjectViews)
		{
			uboView.BindUniformBufferObject();
		}

	}
}

void dooms::graphics::Material::UnBindMaterial() const
{
	if (FixedMaterial::GetIsFixedMaterialExist() == false)
	{

		if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
			{
				GraphicsAPI::BindShader(0, (static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)));
			}

			GraphicsAPI::BindInputLayoutForD3D(0);
		}
		else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(MATERIAL_TAG, 0))
			{
				GraphicsAPI::BindShader(0, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
			}		
		}

		for (UINT32 i = 0; i < mTargetTextures.size(); i++)
		{
			if (IsValid(mTargetTextures[i]) == true)
			{
				mTargetTextures[i]->UnBindTexture();
			}
		}

		for (const UniformBufferObjectView& uboView : mTargetUniformBufferObjectViews)
		{
			uboView.UnBindUniformBufferObject();
		}

	}
}

bool dooms::graphics::Material::IsMaterialCreated() const
{
	return (mMaterialStatus == eStatus::SUCCESS);
}

dooms::graphics::UniformBufferObjectView* dooms::graphics::Material::GetUniformBufferObjectViewFromUBOName(const char* const uniformBufferObjectName)
{
	UniformBufferObjectView* uboView = nullptr;

	D_DEBUG_LOG(eLogType::D_WARNING, "Calling Material::GetUniformBufferObjectView function with string ubo name is slow operator. Please use the function with index parameter");

	for(UniformBufferObjectView& targetUboView : mTargetUniformBufferObjectViews)
	{
		const UniformBufferObject* const ubo = targetUboView.GetTargetUniformBufferObject();
		if(IsValid(ubo))
		{
			if(ubo->GetUniformBlockName() == uniformBufferObjectName)
			{
				uboView = &targetUboView;
				break;
			}
		}
	}

	D_ASSERT(IsValid(uboView));

	return uboView;
}

