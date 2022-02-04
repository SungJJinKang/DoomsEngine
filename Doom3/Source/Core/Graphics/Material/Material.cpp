#include "Material.h"

#include <Asset/ShaderAsset.h>

#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include "FixedMaterial.h"
#include "../Buffer/UniformBufferObject/UniformBufferObjectManager.h"
#include <Asset/TextureAsset.h>
#include "../Texture/TextureView.h"

UINT64 dooms::graphics::Material::BOUND_SHADER_ID[GRAPHICS_PIPELINE_STAGE_COUNT]{ (UINT64)-1, (UINT64)-1, (UINT64)-1};
UINT64 dooms::graphics::Material::BOUND_INPUT_LAYOUT_ID{(UINT64)-1};

bool dooms::graphics::Material::AttachShaderToMaterial(dooms::asset::ShaderAsset* const shaderAsset, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
{
	D_ASSERT(IsValid(shaderAsset));
	D_ASSERT(shaderAsset->GetShaderObject(shaderType).IsValid());

	bool isSuccess = true;

	if (IsValid(shaderAsset) && (shaderType != dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY))
	{
		CreateMaterialObjectIfNotExist();

		shaderAsset->CompileShaderIfNotCompiled();
		
		if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
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
		else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			if (shaderAsset->IsShaderObjectSuccessfullyCreated(shaderType))
			{
				DestroyShaderFromMaterial(shaderType);
				isSuccess &= GraphicsAPI::AttachShaderToMaterial(mPipeLineShaderView[shaderType].GetBufferIDRef(), mProgramIDForOpenGL.GetBufferIDRef(), shaderAsset->GetShaderObject(shaderType), shaderType);
				
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
		if (IsValid(shaderAssets[shaderTypeIndex]))
		{
			SetShaderAsset(shaderAssets[shaderTypeIndex], static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(shaderTypeIndex));
		}
	}
}

bool dooms::graphics::Material::IsHasAnyValidShaderObject() const
{
	bool isHasAnyValidShaderObject = false;

	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (mProgramIDForOpenGL.IsValid())
		{
			isHasAnyValidShaderObject = true;
		}
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
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
	mTargetUniformBufferObjectViews{}
{

}

dooms::graphics::Material::Material(dooms::asset::ShaderAsset* const shaderAsset)
	:
	mMaterialStatus(eStatus::READY),
	mProgramIDForOpenGL{},
	mShaderAsset{ nullptr },
	mPipeLineShaderView{},
	mTargetUniformBufferObjectViews{}
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
	mTargetUniformBufferObjectViews{}
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
	mTargetUniformBufferObjectViews{}
{
	SetShaderAsset(shaderAssets);
}

void dooms::graphics::Material::CreateMaterialObjectIfNotExist()
{
	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
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
	if(dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (mProgramIDForOpenGL.IsValid())
		{
			GraphicsAPI::DestroyMaterial(mProgramIDForOpenGL);
			mProgramIDForOpenGL.Reset();
		}
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
		{
			DestroyShaderFromMaterial(static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex));
		}

		
	}

	mTargetUniformBufferObjectViews.clear();

	mMaterialStatus = eStatus::READY;
}

void dooms::graphics::Material::DestroyShaderFromMaterial(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType)
{
	if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		if (mProgramIDForOpenGL.IsValid() && IsValid(mShaderAsset[shaderType]) && mShaderAsset[shaderType]->GetShaderObject(shaderType).IsValid())
		{
			GraphicsAPI::DetachShaderFromMaterial(mPipeLineShaderView[shaderType], mProgramIDForOpenGL, mShaderAsset[shaderType]->GetShaderObject(shaderType));
		}
	}
	else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == dooms::graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		if(mPipeLineShaderView[shaderType].IsValid())
		{
			GraphicsAPI::DetachShaderFromMaterial
			(
				mPipeLineShaderView[shaderType], 
				mProgramIDForOpenGL, 
				(IsValid(mShaderAsset[shaderType]) == true) ? static_cast<UINT64>(mShaderAsset[shaderType]->GetShaderObject(shaderType)) : static_cast<UINT64>(0)
			);
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
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
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
		else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
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

		if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
			{
				if (mPipeLineShaderView[pipeLineStageIndex].IsValid() == true)
				{
					if(BOUND_SHADER_ID[pipeLineStageIndex] != mPipeLineShaderView[pipeLineStageIndex].GetBufferID())
					{
						BOUND_SHADER_ID[pipeLineStageIndex] = mPipeLineShaderView[pipeLineStageIndex].GetBufferID();
						GraphicsAPI::BindShader(mPipeLineShaderView[pipeLineStageIndex], (static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)));
					}
				}
			}

			D_ASSERT(IsValid(mShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]) && mShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER));
			if (IsValid(mShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]) && mShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]->IsShaderObjectSuccessfullyCreated(graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER))
			{
				const graphics::BufferID& inputLayoutForD3D = mShaderAsset[graphics::GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER]->GetInputLayoutForD3D();
				D_ASSERT(inputLayoutForD3D.IsValid());
				if (inputLayoutForD3D.IsValid())
				{
					if (BOUND_INPUT_LAYOUT_ID != inputLayoutForD3D.GetBufferID())
					{
						BOUND_INPUT_LAYOUT_ID = inputLayoutForD3D;
						GraphicsAPI::BindInputLayoutForD3D(inputLayoutForD3D);
					}
				}
			}
		}
			
			
		else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			D_ASSERT(mProgramIDForOpenGL.IsValid());
			if (mProgramIDForOpenGL.IsValid() == true)
			{
				if (BOUND_SHADER_ID[0] != mProgramIDForOpenGL.GetBufferID())
				{
					BOUND_SHADER_ID[0] = mProgramIDForOpenGL;
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

		if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
		{
			for (size_t pipeLineStageIndex = 0; pipeLineStageIndex < GRAPHICS_PIPELINE_STAGE_COUNT; pipeLineStageIndex++)
			{
				if (BOUND_SHADER_ID[pipeLineStageIndex] != 0)
				{
					BOUND_SHADER_ID[pipeLineStageIndex] = 0;
					GraphicsAPI::BindShader(0, (static_cast<dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage>(pipeLineStageIndex)));
				}
			}

			if (BOUND_INPUT_LAYOUT_ID != 0)
			{
				BOUND_INPUT_LAYOUT_ID = 0;
				GraphicsAPI::BindInputLayoutForD3D(0);
			}
		}
		else if (dooms::graphics::GraphicsAPIManager::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			if (BOUND_SHADER_ID[0] != 0)
			{
				BOUND_SHADER_ID[0] = 0;
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

