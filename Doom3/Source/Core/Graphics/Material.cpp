#include "Material.h"

#include "Graphics_Core.h"
#include "../Asset/ShaderAsset.h"

using namespace doom::graphics;


void Material::SetShaderAsset(ShaderAsset& shaderAsset)
{
	mShaderAsset = &shaderAsset;

	D_ASSERT(this->mID == 0); // error : you're overlapping program

	unsigned int vertexId = shaderAsset.GetVertexId();
	unsigned int fragmentId = shaderAsset.GetFragmentId();
	unsigned int geometryId = shaderAsset.GetGeometryId();
	D_ASSERT(vertexId != 0 || fragmentId != 0 || geometryId != 0);


	this->mID = glCreateProgram();

	if (vertexId != 0)
	{
		glAttachShader(this->mID, vertexId);
	}

	if (fragmentId != 0)
	{
		glAttachShader(this->mID, fragmentId);
	}

	if (geometryId != 0)
	{
		glAttachShader(this->mID, geometryId);
	}

	glLinkProgram(this->mID);

#ifdef DEBUG_MODE
	int isSuccess = 0;
	glGetProgramiv(this->mID, GL_LINK_STATUS, &isSuccess);
	if (!isSuccess)
	{
		char infoLog[512];
		glGetProgramInfoLog(this->mID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
#endif

	if (isSuccess == true)
	{

		int uniformBlockCount = GetUniformBlocksCount();
		for (int i = 0; i < uniformBlockCount; i++)
		{
			glGetActiveUniform(this->mID, ) // https://www.khronos.org/opengl/wiki/GLAPI/glGetActiveUniforms
			glGetActiveUniforms
		}

	}
	
}


Material::Material(ShaderAsset& shaderAsset) : mID{ 0 }, mShaderAsset{ nullptr }, mTargetTextures{}, mUniformBlockCount{ 0 }
{
	this->SetShaderAsset(shaderAsset);
}

Material::~Material()
{
	if (this->mID != 0)
	{
		glDeleteProgram(this->mID);
	}
}

void Material::AddTexture(Texture& texture)
{
	this->mTargetTextures.push_back(&texture);
}

void Material::AddTextures(std::vector<Texture*> textures)
{
	this->mTargetTextures.insert(this->mTargetTextures.end(), textures.begin(), textures.end());
}

/*
void Material::SetUniformBlockPoint(const std::string uniformBlockName, unsigned int bindingPoint)
{
	unsigned int uniformBlockIndex = glGetUniformBlockIndex(this->mID, uniformBlockName.c_str());
	glUniformBlockBinding(this->mID, uniformBlockIndex, bindingPoint);
}
*/

int Material::GetUniformBlocksCount()
{
	D_ASSERT(this->mID != 0);

	int uniformBlockCount = 0;
	glGetProgramiv(this->mID, GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlockCount);
	this->mUniformBlockCount = uniformBlockCount;
}

