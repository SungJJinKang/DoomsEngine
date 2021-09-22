#include "Material.h"

#include "../Graphics_Core.h"
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

	unsigned int vertexId = shaderAsset->GetVertexId();
	unsigned int fragmentId = shaderAsset->GetFragmentId();
	unsigned int geometryId = shaderAsset->GetGeometryId();
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


	int isSuccess = 0;
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


doom::graphics::Material::Material() : mProgramID{ 0}, mShaderAsset{ nullptr }
{
}

Material::Material(::doom::asset::ShaderAsset* shaderAsset) : mProgramID{0}, mShaderAsset{ nullptr }
{
	if (shaderAsset != nullptr)
	{
		SetShaderAsset(shaderAsset);
	}

}

Material::~Material()
{
	if (mProgramID.Get() != 0)
	{
		glDeleteProgram(mProgramID);
	}
}

bool doom::graphics::Material::IsGenerated()
{
	return mProgramID != 0;
}

void Material::AddTexture(unsigned int bindingPoint, Texture* texture)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures[bindingPoint] = texture;
}

void Material::AddTexture(unsigned int bindingPoint, ::doom::asset::TextureAsset* textureAsset)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures[bindingPoint] = textureAsset->mTexture;
}

void doom::graphics::Material::AddTextures(const std::array<Texture*, MAX_TEXTURE_COUNT>& textures)
{
	D_ASSERT(IsGenerated() == true);
	mTargetTextures = textures;
}

void doom::graphics::Material::UseProgram()
{
	D_ASSERT(mProgramID != 0);

	if (FixedMaterial::GetIsFixedMaterialExist() == false)
	{
		if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(MATERIAL_TAG, mProgramID))
		{
			for (unsigned int i = 0; i < mTargetTextures.size(); i++)
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
void Material::SetUniformBlockPoint(const std::string uniformBlockName, unsigned int bindingPoint)
{
	unsigned int uniformBlockIndex = glGetUniformBlockIndex(data, uniformBlockName.c_str());
	glUniformBlockBinding(data, uniformBlockIndex, bindingPoint);
}
*/

int Material::GetUniformBlocksCount()
{
	D_ASSERT(mProgramID != 0);

	int uniformBlockCount = 0;
	glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlockCount);
	return uniformBlockCount;
}

void Material::InitUniformBufferObject()
{
	int uniformBlockCount = GetUniformBlocksCount();
	for (int i = 0; i < uniformBlockCount; i++)
	{
		int uniformBlockBindingPoint = 0;
		glGetActiveUniformBlockiv(mProgramID, i, GL_UNIFORM_BLOCK_BINDING, &uniformBlockBindingPoint); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetActiveUniformBlock.xhtml
		
		int uniformBlockSize = 0;
		glGetActiveUniformBlockiv(mProgramID, i, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
		
		UniformBufferObject& uniformBufferObject = UniformBufferObjectManager::GetSingleton()->GetOrGenerateUniformBufferObject(uniformBlockBindingPoint, uniformBlockSize);
		mUniformBufferObjects[i] = &uniformBufferObject;

		/*
		int elementCount = 0;
		glGetActiveUniformBlockiv(data, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &elementCount);

		int* elementList = new int[100];
		glGetActiveUniformBlockiv(data, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, elementList);

		for (int i = 0; i < elementCount; i++)
		{
			
		}
		*/
	}

}

