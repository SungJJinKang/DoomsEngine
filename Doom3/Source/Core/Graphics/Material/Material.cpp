#include "Material.h"

#include <Asset/ShaderAsset.h>

#include "FixedMaterial.h"

#include "../Buffer/UniformBufferObjectManager.h"
#include <Asset/TextureAsset.h>

#include "../Texture/Texture.h"

using namespace dooms::graphics;


void Material::SetShaderAsset(::dooms::asset::ShaderAsset* shaderAsset)
{
	D_ASSERT(IsValid(shaderAsset) == true);
	D_ASSERT(shaderAsset->GetIsShaderCompiled() == true);

	mShaderAsset = shaderAsset;

	D_ASSERT(mProgramID == 0); // error : you're overlapping program

	UINT32 vertexId = shaderAsset->GetVertexId();
	UINT32 fragmentId = shaderAsset->GetFragmentId();
	UINT32 geometryId = shaderAsset->GetGeometryId();
	D_ASSERT(vertexId != 0 || fragmentId != 0 || geometryId != 0);


	mProgramID = GraphicsAPI::CreateMaterial();

	if (vertexId != 0)
	{
		GraphicsAPI::AttachShaderToMaterial(mProgramID, vertexId);
	}

	if (fragmentId != 0)
	{
		GraphicsAPI::AttachShaderToMaterial(mProgramID, fragmentId);
	}

	if (geometryId != 0)
	{
		GraphicsAPI::AttachShaderToMaterial(mProgramID, geometryId);
	}

	const bool isSuccessLinkMaterial = GraphicsAPI::LinkMaterial(mProgramID);
	
	if (isSuccessLinkMaterial)
	{
		InitUniformBufferObject();
	}	
}


dooms::graphics::Material::Material() : mProgramID{ INVALID_BUFFER_ID }, mShaderAsset{ nullptr }
{
}

Material::Material(::dooms::asset::ShaderAsset* shaderAsset) : mProgramID{0}, mShaderAsset{ nullptr }
{
	if (IsValid(shaderAsset) == true)
	{
		SetShaderAsset(shaderAsset);
	}

}

void Material::DestroyMaterialBufferObject()
{
	if (mProgramID.GetBufferID() != INVALID_BUFFER_ID)
	{
		GraphicsAPI::DestroyMaterial(mProgramID);
		mProgramID = 0;
	}
}

Material::~Material()
{
	DestroyMaterialBufferObject();
}

bool dooms::graphics::Material::IsGenerated() const
{
	return mProgramID != 0;
}

void Material::AddTexture(UINT32 bindingPoint, Texture* texture)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures[bindingPoint] = texture;
}

void Material::AddTexture(UINT32 bindingPoint, ::dooms::asset::TextureAsset* textureAsset)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures[bindingPoint] = textureAsset->GetDefaultTextureObject();
}

void dooms::graphics::Material::AddTextures(const std::array<const Texture*, MAX_TEXTURE_COUNT>& textures)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures = textures;
}

void dooms::graphics::Material::UseProgram() const
{
	D_ASSERT(mProgramID != 0);

	if (FixedMaterial::GetIsFixedMaterialExist() == false)
	{
		if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(MATERIAL_TAG, mProgramID))
		{
			for (UINT32 i = 0; i < mTargetTextures.size(); i++)
			{
				if (IsValid(mTargetTextures[i]) == true)
				{
					mTargetTextures[i]->BindTextureWithUnit(i);
				}
			}
			GraphicsAPI::BindMaterial(mProgramID);
		}
	}

	
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
	D_ASSERT(mProgramID != 0);

	INT32 uniformBlockCount = 0;

	switch (GraphicsAPI::GetGraphicsAPIType())
	{
	case eGraphicsAPIType::OpenGL:
		glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlockCount);
		break;

	case eGraphicsAPIType::DX11:

		break;

	default:
		D_ASSERT(false);
	}

	
	
	return uniformBlockCount;
}

void Material::InitUniformBufferObject()
{
	INT32 uniformBlockCount = GetUniformBlocksCount();
	for (INT32 i = 0; i < uniformBlockCount; i++)
	{
		INT32 uniformBlockBindingPoint = 0;
		INT32 uniformBlockSize = 0;

		switch (GraphicsAPI::GetGraphicsAPIType())
		{
		case eGraphicsAPIType::OpenGL:
			glGetActiveUniformBlockiv(mProgramID, i, GL_UNIFORM_BLOCK_BINDING, &uniformBlockBindingPoint); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetActiveUniformBlock.xhtml
			glGetActiveUniformBlockiv(mProgramID, i, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);

			break;

		case eGraphicsAPIType::DX11:

			break;

		default:
			D_ASSERT(false);
		}

		UniformBufferObject& uniformBufferObject = UniformBufferObjectManager::GetSingleton()->GetOrGenerateUniformBufferObject(uniformBlockBindingPoint, uniformBlockSize);
		mUniformBufferObjects[i] = &uniformBufferObject;

		/*
		INT32 elementCount = 0;
		glGetActiveUniformBlockiv(data, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &elementCount);

		INT32* elementList = new INT32[100];
		glGetActiveUniformBlockiv(data, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, elementList);

		for (INT32 i = 0; i < elementCount; i++)
		{
			
		}
		*/
	}

}

