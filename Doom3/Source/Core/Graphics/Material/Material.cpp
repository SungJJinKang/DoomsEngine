#include "Material.h"

#include <Asset/ShaderAsset.h>

#include "FixedMaterial.h"

#include "../Buffer/UniformBufferObjectManager.h"
#include <Asset/TextureAsset.h>
#include "../Texture/Texture.h"

using namespace doom::graphics;


void Material::SetShaderAsset(::doom::asset::ShaderAsset* shaderAsset)
{
	D_ASSERT(shaderAsset != nullptr);

	mShaderAsset = shaderAsset;

	D_ASSERT(mProgramID == 0); // error : you're overlapping program

	UINT32 vertexId = shaderAsset->GetVertexId();
	UINT32 fragmentId = shaderAsset->GetFragmentId();
	UINT32 geometryId = shaderAsset->GetGeometryId();
	D_ASSERT(vertexId != 0 || fragmentId != 0 || geometryId != 0);


	mProgramID = glCreateProgram();

	if (vertexId != 0)
	{
		glAttachShader(mProgramID, vertexId);
	}

	if (fragmentId != 0)
	{
		glAttachShader(mProgramID, fragmentId);
	}

	if (geometryId != 0)
	{
		glAttachShader(mProgramID, geometryId);
	}

	glLinkProgram(mProgramID);


	INT32 isSuccess = 0;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &isSuccess);
#ifdef DEBUG_MODE
	if (!isSuccess)
	{
		char infoLog[512];
		glGetProgramInfoLog(mProgramID, 512, NULL, infoLog);
		D_DEBUG_LOG({ "Shader File Name : ", shaderAsset->GetAssetFileName(), " - SHADER::PROGRAM::LINKING_FAILED", infoLog}, eLogType::D_ERROR);
	}
#endif

	if (isSuccess > 0)
	{
		InitUniformBufferObject();
	
	}
	
}


doom::graphics::Material::Material() : mProgramID{ INVALID_BUFFER_ID }, mShaderAsset{ nullptr }
{
}

Material::Material(::doom::asset::ShaderAsset* shaderAsset) : mProgramID{0}, mShaderAsset{ nullptr }
{
	if (shaderAsset != nullptr)
	{
		SetShaderAsset(shaderAsset);
	}

}

void Material::DestroyMaterialBufferObject()
{
	if (mProgramID.GetBufferID() != INVALID_BUFFER_ID)
	{
		glDeleteProgram(mProgramID);
		mProgramID = 0;
	}
}

Material::~Material()
{
	DestroyMaterialBufferObject();
}

bool doom::graphics::Material::IsGenerated() const
{
	return mProgramID != 0;
}

void Material::AddTexture(UINT32 bindingPoint, Texture* texture)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures[bindingPoint] = texture;
}

void Material::AddTexture(UINT32 bindingPoint, ::doom::asset::TextureAsset* textureAsset)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures[bindingPoint] = textureAsset->GetDefaultTextureObject();
}

void doom::graphics::Material::AddTextures(const std::array<const Texture*, MAX_TEXTURE_COUNT>& textures)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures = textures;
}

void doom::graphics::Material::UseProgram() const
{
	D_ASSERT(mProgramID != 0);

	if (FixedMaterial::GetIsFixedMaterialExist() == false)
	{
		if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(MATERIAL_TAG, mProgramID))
		{
			for (UINT32 i = 0; i < mTargetTextures.size(); i++)
			{
				if (mTargetTextures[i] != nullptr)
				{
					mTargetTextures[i]->BindTextureWithUnit(i);
				}
			}
			glUseProgram(mProgramID);
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
	glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlockCount);
	return uniformBlockCount;
}

void Material::InitUniformBufferObject()
{
	INT32 uniformBlockCount = GetUniformBlocksCount();
	for (INT32 i = 0; i < uniformBlockCount; i++)
	{
		INT32 uniformBlockBindingPoint = 0;
		glGetActiveUniformBlockiv(mProgramID, i, GL_UNIFORM_BLOCK_BINDING, &uniformBlockBindingPoint); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetActiveUniformBlock.xhtml
		
		INT32 uniformBlockSize = 0;
		glGetActiveUniformBlockiv(mProgramID, i, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
		
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

