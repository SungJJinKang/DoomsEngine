#include "Material.h"

#include <Asset/ShaderAsset.h>

#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include "FixedMaterial.h"
#include "../Buffer/UniformBufferObjectManager.h"
#include <Asset/TextureAsset.h>
#include "../Texture/TextureView.h"

using namespace dooms::graphics;


void Material::SetShaderAsset(::dooms::asset::ShaderAsset* shaderAsset)
{
	D_ASSERT(IsValid(shaderAsset) == true);
	D_ASSERT(shaderAsset->GetIsShaderCompiled() == true);

	mShaderAsset = shaderAsset;

	D_ASSERT(mProgramID.IsValid() == false); // error : you're overlapping program
	D_ASSERT(shaderAsset->GetVertexId().IsValid() || shaderAsset->GetFragmentId().IsValid() || shaderAsset->GetGeometryId().IsValid());


	mProgramID = GraphicsAPI::CreateMaterial();

	if (shaderAsset->GetVertexId().IsValid())
	{
		GraphicsAPI::AttachShaderToMaterial(mProgramID, shaderAsset->GetVertexId());
	}

	if (shaderAsset->GetFragmentId().IsValid())
	{
		GraphicsAPI::AttachShaderToMaterial(mProgramID, shaderAsset->GetFragmentId());
	}

	if (shaderAsset->GetGeometryId().IsValid())
	{
		GraphicsAPI::AttachShaderToMaterial(mProgramID, shaderAsset->GetGeometryId());
	}

	const bool isSuccessLinkMaterial = GraphicsAPI::LinkMaterial(mProgramID);
	
	/*
	if (isSuccessLinkMaterial)
	{
		InitUniformBufferObject();
	}
	*/

}


dooms::graphics::Material::Material() : mProgramID{ }, mShaderAsset{ nullptr }
{
}

Material::Material(::dooms::asset::ShaderAsset* shaderAsset) : mProgramID{}, mShaderAsset{ nullptr }
{
	if (IsValid(shaderAsset) == true)
	{
		SetShaderAsset(shaderAsset);
	}

}

void Material::DestroyMaterialObject()
{
	if (mProgramID.IsValid())
	{
		GraphicsAPI::DestroyMaterial(mProgramID);
		mProgramID.Reset();
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
	return mProgramID.IsValid();
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
	D_ASSERT(mProgramID.IsValid());

	if (FixedMaterial::GetIsFixedMaterialExist() == false)
	{
		if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(MATERIAL_TAG, mProgramID))
		{
			for (UINT32 i = 0; i < mTargetTextures.size(); i++)
			{
				if (IsValid(mTargetTextures[i]) == true)
				{
					mTargetTextures[i]->BindTexture();
				}
			}

			if(dooms::graphics::GraphicsAPI::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::DX11_10)
			{
				const UINT64 vertexShader = GetShaderAsset()->GetVertexId();
				if(vertexShader != NULL)
				{
					GraphicsAPI::BindMaterial(vertexShader);
				}
				
				GraphicsAPI::BindMaterial(GetShaderAsset()->GetFragmentId());
				GraphicsAPI::BindMaterial(GetShaderAsset()->GetGeometryId());
			}
			else if (dooms::graphics::GraphicsAPI::GetCurrentAPIType() == GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::BindMaterial(mProgramID);
			}
			
		}
	}

	
}

INT32 Material::GetUniformLocation(const char* str) const
{
	return GraphicsAPI::GetConstantBufferUniformLocation(mProgramID, str);
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
	D_ASSERT(mProgramID.IsValid());
	
	return GraphicsAPI::GetConstantBufferBlockCount(mProgramID);
}

void Material::InitUniformBufferObject
(
	const std::string& uniformBufferName,
	const UINT64 uniformBufferSize,
	const UINT32 bindingPoint,
	const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
)
{
	UniformBufferObject* const uniformBufferObject = UniformBufferObjectManager::GetSingleton()->GetOrGenerateUniformBufferObject(uniformBufferName, uniformBufferSize, bindingPoint, targetPipeLineStage, nullptr);
	mUniformBufferObjects.push_back(uniformBufferObject);
}

const dooms::asset::ShaderAsset* Material::GetShaderAsset() const
{
	return mShaderAsset;
}

