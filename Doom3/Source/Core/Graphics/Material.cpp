#include "Material.h"

#include "Graphics_Core.h"
#include "../Asset/ShaderAsset.h"

#include "Buffer/UniformBufferObjectManager.h"
#include "../Asset/TextureAsset.h"

using namespace doom::graphics;


void Material::SetShaderAsset(ShaderAsset& shaderAsset)
{
	mShaderAsset = &shaderAsset;

	D_ASSERT(this->mProgramID == 0); // error : you're overlapping program

	unsigned int vertexId = shaderAsset.GetVertexId();
	unsigned int fragmentId = shaderAsset.GetFragmentId();
	unsigned int geometryId = shaderAsset.GetGeometryId();
	D_ASSERT(vertexId != 0 || fragmentId != 0 || geometryId != 0);


	this->mProgramID = glCreateProgram();

	if (vertexId != 0)
	{
		glAttachShader(this->mProgramID, vertexId);
	}

	if (fragmentId != 0)
	{
		glAttachShader(this->mProgramID, fragmentId);
	}

	if (geometryId != 0)
	{
		glAttachShader(this->mProgramID, geometryId);
	}

	glLinkProgram(this->mProgramID);


	int isSuccess = 0;
	glGetProgramiv(this->mProgramID, GL_LINK_STATUS, &isSuccess);
#ifdef DEBUG_MODE
	if (!isSuccess)
	{
		char infoLog[512];
		glGetProgramInfoLog(this->mProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
#endif

	if (isSuccess > 0)
	{
		InitUniformBufferObject();
	
	}
	
}


doom::graphics::Material::Material() : mProgramID{ }, mShaderAsset{ nullptr }
{
}

Material::Material(ShaderAsset& shaderAsset) : mProgramID{ }, mShaderAsset{ nullptr }
{
	this->SetShaderAsset(shaderAsset);
}

Material::~Material()
{
	if (this->mProgramID.GetReference() != 0)
	{
		glDeleteProgram(this->mProgramID);
	}
}

bool doom::graphics::Material::IsGenerated()
{
	return this->mProgramID != 0;
}

void Material::AddTexture(unsigned int bindingPoint, Texture* texture)
{
	this->mTargetTextures[bindingPoint] = texture;
}

void Material::AddTexture(unsigned int bindingPoint, ::doom::TextureAsset& textureAsset)
{
	this->mTargetTextures[bindingPoint] = textureAsset.mTexture;
}

void Material::AddTextures(std::array<Texture*, MAX_TEXTURE_COUNT> textures)
{
	this->mTargetTextures = textures;
}

/*
void Material::SetUniformBlockPoint(const std::string uniformBlockName, unsigned int bindingPoint)
{
	unsigned int uniformBlockIndex = glGetUniformBlockIndex(this->data, uniformBlockName.c_str());
	glUniformBlockBinding(this->data, uniformBlockIndex, bindingPoint);
}
*/

int Material::GetUniformBlocksCount()
{
	D_ASSERT(this->mProgramID != 0);

	int uniformBlockCount = 0;
	glGetProgramiv(this->mProgramID, GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlockCount);
	return uniformBlockCount;
}

void Material::InitUniformBufferObject()
{
	int uniformBlockCount = GetUniformBlocksCount();
	for (int i = 0; i < uniformBlockCount; i++)
	{
		int uniformBlockBindingPoint = 0;
		glGetActiveUniformBlockiv(this->mProgramID, i, GL_UNIFORM_BLOCK_BINDING, &uniformBlockBindingPoint); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetActiveUniformBlock.xhtml
		
		int uniformBlockSize = 0;
		glGetActiveUniformBlockiv(this->mProgramID, i, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
		
		auto& uniformBufferObject = UniformBufferObjectManager::GetSingleton()->GetOrGenerateUniformBufferObject(uniformBlockBindingPoint, uniformBlockSize);
		this->mUniformBufferObjects[i] = &uniformBufferObject;

		/*
		int elementCount = 0;
		glGetActiveUniformBlockiv(this->data, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &elementCount);

		int* elementList = new int[100];
		glGetActiveUniformBlockiv(this->data, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, elementList);

		for (int i = 0; i < elementCount; i++)
		{
			
		}
		*/
	}

}

