#include "Material.h"

#include <Asset/ShaderAsset.h>

#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include "FixedMaterial.h"
#include "../Buffer/UniformBufferObject/UniformBufferObjectManager.h"
#include <Asset/TextureAsset.h>
#include "../Texture/TextureView.h"

using namespace dooms::graphics;

bool Material::CreateMeterialObject()
{
	D_ASSERT(IsValid(mShaderAsset));
	D_ASSERT(mShaderAsset->IsHasAnyValidShaderObject() == true);

	bool isSuccess = true;

	if(IsValid(mShaderAsset))
	{
		DestroyMaterialObjectIfExist();

		mShaderAsset->CompileShaderIfNotCompiled();

		if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			mProgramIDForOpenGL = GraphicsAPI::CreateMaterial();
			if(mProgramIDForOpenGL.IsValid())
			{
				for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
				{
					if (mShaderAsset->IsShaderObjectSuccessfullyCreated(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)))
					{
						isSuccess &= GraphicsAPI::AttachShaderToMaterial(mProgramIDForOpenGL, mShaderAsset->GetShaderObject(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)), static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex));
						D_ASSERT(isSuccess == true);
					}
				}

				const bool isSuccessLinkMaterial = GraphicsAPI::LinkMaterial(mProgramIDForOpenGL);
				D_ASSERT(isSuccessLinkMaterial == true);

				isSuccess &= isSuccessLinkMaterial;
			}
			else
			{
				isSuccess = false;
			}
		}
		else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
			{
				if (mShaderAsset->IsShaderObjectSuccessfullyCreated(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)))
				{
					isSuccess &= GraphicsAPI::AttachShaderToMaterial(mPipeLineShaderObject[pipeLineStageIndex], mShaderAsset->GetShaderObject(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)), static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex));
					D_ASSERT(isSuccess == true);
				}
			}
		}
	}
	else
	{
		isSuccess = false;
	}

	if(isSuccess == true)
	{
		mMaterialStatus = eStatus::SUCCESS;
	}
	else
	{
		mMaterialStatus = eStatus::FAIL;
	}

	D_ASSERT(isSuccess == true);
	return isSuccess;
}

void Material::SetShaderAsset(dooms::asset::ShaderAsset* const shaderAsset)
{
	D_ASSERT(IsValid(shaderAsset) == true);
	D_ASSERT(shaderAsset->IsHasAnyValidShaderObject() == true);
	D_ASSERT(IsHasAnyValidShaderObject() == false);

	mShaderAsset = shaderAsset;
	CreateMeterialObject();

	D_ASSERT(IsHasAnyValidShaderObject() == true); // error : you're overlapping program
}

bool Material::IsHasAnyValidShaderObject() const
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
			if (mPipeLineShaderObject[pipeLineStageIndex].IsValid() == true)
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
	mPipeLineShaderObject{},
	mTargetUniformBufferObjectViews{}
{

}

Material::Material(dooms::asset::ShaderAsset* const shaderAsset)
	:
	mMaterialStatus(eStatus::READY),
	mProgramIDForOpenGL{},
	mShaderAsset{ nullptr },
	mPipeLineShaderObject{},
	mTargetUniformBufferObjectViews{}
{
	if (IsValid(shaderAsset) == true)
	{
		SetShaderAsset(shaderAsset);
	}
}

void Material::DestroyMaterialObjectIfExist()
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
			if (mPipeLineShaderObject[pipeLineStageIndex].IsValid() == true)
			{
				GraphicsAPI::DestroyMaterial(mPipeLineShaderObject[pipeLineStageIndex]);
			}
		}
	}

	mMaterialStatus = eStatus::READY;
}



void Material::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestroyMaterialObjectIfExist();
}


Material::~Material()
{
	DestroyMaterialObjectIfExist();
}


void Material::AddTexture(UINT32 bindingPoint, TextureView* texture)
{
	D_ASSERT(IsHasAnyValidShaderObject() == true);
	mTargetTextures[bindingPoint] = texture;
}

void Material::AddTexture(const UINT32 bindingPoint, const dooms::asset::TextureAsset* const textureAsset)
{
	D_ASSERT(IsHasAnyValidShaderObject() == true);
	mTargetTextures.push_back(textureAsset->GenerateTextureView(bindingPoint, GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
}

void dooms::graphics::Material::AddTextures(const std::vector<const TextureView*>& textures)
{
	D_ASSERT(IsHasAnyValidShaderObject() == true);
	mTargetTextures = textures;
}

void dooms::graphics::Material::UseProgram() const
{
	D_ASSERT(mProgramIDForOpenGL.IsValid());

	if (FixedMaterial::GetIsFixedMaterialExist() == false)
	{
		if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(MATERIAL_TAG, mProgramIDForOpenGL))
		{
			if(dooms::graphics::GraphicsAPI::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
			{
				for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
				{
					if (mPipeLineShaderObject[pipeLineStageIndex].IsValid() == true)
					{
						GraphicsAPI::BindShader(mPipeLineShaderObject[pipeLineStageIndex], (static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)));
					}
				}
			}
			else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				if (mProgramIDForOpenGL.IsValid() == true)
				{
					GraphicsAPI::BindShader(mProgramIDForOpenGL, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
				}
			}

			for (UINT32 i = 0; i < mTargetTextures.size(); i++)
			{
				if (IsValid(mTargetTextures[i]) == true)
				{
					mTargetTextures[i]->BindTexture();
				}
			}
			
		}
	}

	
}

bool Material::IsMaterialCreated() const
{
	return (mMaterialStatus == eStatus::SUCCESS);
}

UniformBufferObjectView* Material::GetUniformBufferObjectViewFromUBOName(const char* const uniformBufferObjectName)
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

	return uboView;
}

