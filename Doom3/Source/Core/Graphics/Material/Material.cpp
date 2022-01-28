#include "Material.h"

#include <Asset/ShaderAsset.h>

#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include "FixedMaterial.h"
#include "../Buffer/UniformBufferObject/UniformBufferObjectManager.h"
#include <Asset/TextureAsset.h>
#include "../Texture/TextureView.h"

using namespace dooms::graphics;

bool Material::CreateShaderObject()
{
	D_ASSERT(IsValid(mShaderAsset));
	D_ASSERT(mShaderAsset->IsHasAnyValidShaderObject() == true);

	bool isSuccess = true;

	if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		mProgramIDForOpenGL = GraphicsAPI::CreateMaterial();

		for(size_t pipeLineStageIndex = 0 ; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT ; pipeLineStageIndex++)
		{
			if (mShaderAsset->IsShaderObjectSuccessfullyCreated(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)))
			{
				isSuccess &= GraphicsAPI::AttachShaderToMaterial(mProgramIDForOpenGL, mShaderAsset->GetShaderObject(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)), static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex));
			}
		}
		
		const bool isSuccessLinkMaterial = GraphicsAPI::LinkMaterial(mProgramIDForOpenGL);
		D_ASSERT(isSuccessLinkMaterial == true);
	}
	else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
		{
			if (mShaderAsset->IsShaderObjectSuccessfullyCreated(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)))
			{
				isSuccess &= GraphicsAPI::AttachShaderToMaterial(mPipeLineShaderObject[pipeLineStageIndex], mShaderAsset->GetShaderObject(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)), static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex));
			}
		}
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
	CreateShaderObject();

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
	mProgramIDForOpenGL{ },
	mShaderAsset{ nullptr },
	mPipeLineShaderObject{},
	mTargetUniformBufferObjectViews{}
{

}

Material::Material(dooms::asset::ShaderAsset* const shaderAsset)
	:
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

void Material::DestroyMaterialObject()
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
}



void Material::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestroyMaterialObject();
}


Material::~Material()
{
	DestroyMaterialObject();
}

bool dooms::graphics::Material::IsGenerated() const
{
	return mProgramIDForOpenGL.IsValid();
}

void Material::AddTexture(UINT32 bindingPoint, TextureView* texture)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures[bindingPoint] = texture;
}

void Material::AddTexture(const UINT32 bindingPoint, const dooms::asset::TextureAsset* const textureAsset)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures.push_back(textureAsset->GenerateTextureView(bindingPoint, GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER));
}

void dooms::graphics::Material::AddTextures(const std::vector<const TextureView*>& textures)
{
	D_ASSERT(IsGenerated() == true);
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

INT32 Material::GetUniformLocation(const char* str) const
{
	return GraphicsAPI::GetConstantBufferUniformLocation(mProgramIDForOpenGL, str);
}

/*
void Material::SetUniformBlockPoint(const std::string uniformBlockName, UINT32 bindingPoint)
{
	UINT32 uniformBlockIndex = glGetUniformBlockIndex(data, uniformBlockName.c_str());
	glUniformBlockBinding(data, uniformBlockIndex, bindingPoint);
}
*/

INT32 Material::GetUniformBlocksCount() const
{
	D_ASSERT(mProgramIDForOpenGL.IsValid());
	
	return GraphicsAPI::GetConstantBufferBlockCount(mProgramIDForOpenGL);
}

const dooms::asset::ShaderAsset* Material::GetShaderAsset() const
{
	return mShaderAsset;
}

