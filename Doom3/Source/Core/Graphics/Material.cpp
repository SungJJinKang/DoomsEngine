#include "Material.h"

#include "Graphics_Core.h"
#include "../Asset/ShaderAsset.h"

using namespace doom::graphics;


void Material::SetShaderAsset(ShaderAsset& shaderAsset)
{
	mShaderAsset = &shaderAsset;

	D_ASSERT(this->mID == 0); // error : you're overlapping program

	this->mID = glCreateProgram();

	unsigned int vertexId = shaderAsset.GetVertexId();
	unsigned int fragmentId = shaderAsset.GetFragmentId();
	unsigned int geometryId = shaderAsset.GetGeometryId();

	D_ASSERT(vertexId != 0 || fragmentId != 0 || geometryId != 0);

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
}


Material::Material(ShaderAsset& shaderAsset) : mID{ 0 }, mShaderAsset{ nullptr }, mTargetTextures{}
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

