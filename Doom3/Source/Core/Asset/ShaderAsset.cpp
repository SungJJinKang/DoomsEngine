#include <sstream>
#include <array>

#include "ShaderAsset.h"

#include "../API/OpenglAPI.h"
#include "../Core.h"
#include "../Graphics/Material.h"
#include "../../Helper/TextImporter.h"
#include "../../Helper/trim.h"

const std::string doom::asset::ShaderAsset::VertexShaderMacros = "#VERTEX";
const std::string doom::asset::ShaderAsset::FragmentShaderMacros = "#FRAGMENT";
const std::string doom::asset::ShaderAsset::GeometryShaderMacros = "#GEOMETRY";



doom::asset::ShaderAsset::ShaderAsset(ShaderAsset&& shader) noexcept 
	: Asset(std::move(shader)), mVertexId{ shader.mVertexId }, mFragmentId{ shader.mFragmentId }, mGeometryId{ shader.mGeometryId }, 
	mShaderFileText{ std::move(shader.mShaderFileText) }
{
	shader.mVertexId = 0;
	shader.mFragmentId = 0;
	shader.mGeometryId = 0;
}

doom::asset::ShaderAsset& doom::asset::ShaderAsset::operator=(ShaderAsset&& shader) noexcept
{
	Asset::operator=(std::move(shader));

	mVertexId = shader.mVertexId;
	shader.mVertexId = 0;

	mFragmentId = shader.mFragmentId;
	shader.mFragmentId = 0;

	mGeometryId = shader.mGeometryId;
	shader.mGeometryId = 0;

	mShaderFileText = std::move(shader.mShaderFileText);

	return *this;
}

doom::asset::ShaderAsset::~ShaderAsset()
{
	DeleteShaders();
}

void doom::asset::ShaderAsset::DeleteShaders()
{
	if (mVertexId != 0)
	{
		glDeleteShader(mVertexId);
		mVertexId = 0;
	}

	if (mFragmentId != 0)
	{
		glDeleteShader(mFragmentId);
		mFragmentId = 0;
	}

	if (mGeometryId != 0)
	{
		glDeleteShader(mGeometryId);
		mGeometryId = 0;
	}
}

void doom::asset::ShaderAsset::SetShaderText(const std::string& shaderStr) 
{
	mShaderFileText = shaderStr;
}

void doom::asset::ShaderAsset::CompileShaders(const std::string& str)
{
	mVertexId = 0;
	mFragmentId = 0;
	mGeometryId = 0;

	std::array<std::string, 3> shaders = ClassifyShader(str);

	if (shaders[0].size() == 0 && shaders[1].size() == 0 && shaders[2].size() == 0)
		return; // Shader isn't valid

	

	if (shaders[0].size() != 0)
	{
		CompileSpecificShader(shaders[0], ShaderType::Vertex, mVertexId);
	}

	if (shaders[1].size() != 0)
	{
		CompileSpecificShader(shaders[1], ShaderType::Fragment, mFragmentId);
	}

	if (shaders[2].size() != 0)
	{
		CompileSpecificShader(shaders[2], ShaderType::Geometry, mGeometryId);
	}

#ifndef DEBUG_MODE
	mShaderFileText.clear(); //clear shader text file
#endif
}

void doom::asset::ShaderAsset::CompileSpecificShader(const std::string& shaderStr, ShaderType shaderType, unsigned int& shaderId)
{
	unsigned int shaderTypeFlag{};
	if (shaderType == ShaderType::Vertex)
	{
		shaderTypeFlag = GL_VERTEX_SHADER;
	}
	else if (shaderType == ShaderType::Fragment)
	{
		shaderTypeFlag = GL_FRAGMENT_SHADER;

	}
	else if (shaderType == ShaderType::Geometry)
	{
		shaderTypeFlag = GL_GEOMETRY_SHADER;
	}


	shaderId = glCreateShader(shaderTypeFlag);

	const char* shaderCode = shaderStr.c_str();
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);

#ifdef DEBUG_MODE
	checkCompileError(shaderId, shaderType);
#endif
}



std::array<std::string, 3> doom::asset::ShaderAsset::ClassifyShader(const std::string& str)
{
	std::stringstream inputStringStream{ str };
	std::string line;

	ShaderType currentShaderType = ShaderType::None;
	std::string currentShaderStr{};

	std::array<std::string, 3> classifiedShader{};

	

	while (std::getline(inputStringStream, line))
	{
		bool isMacros = false;

		if (CheckIsSharpInclude(line))
		{
			//mAssetPath.relative
			std::filesystem::path targetPath = GetAssetPath();//
			targetPath.remove_filename();

			std::string includeTargetPath = line.substr(line.find("#include", 0) + 8, std::string::npos);
			includeTargetPath = std::trim(includeTargetPath, "\r");
			includeTargetPath = std::trim(includeTargetPath, ' ');
			targetPath.append(includeTargetPath);

			currentShaderStr += ExtractShaderFile(targetPath.make_preferred().string());
			currentShaderStr += '\n';
			continue;
		}
		else if (line.compare(0, 1, "#") == 0)
		{// macros shouldn't have whitespace

			if  
				(line.compare(0, ShaderAsset::VertexShaderMacros.size(), ShaderAsset::VertexShaderMacros, 0) == 0 ||
				line.compare(0, ShaderAsset::FragmentShaderMacros.size(), ShaderAsset::FragmentShaderMacros, 0) == 0 ||
				line.compare(0, ShaderAsset::GeometryShaderMacros.size(), ShaderAsset::GeometryShaderMacros, 0) == 0
				)
			{
				if (currentShaderStr.size() != 0)
				{
					switch (currentShaderType)
					{
					case ShaderType::Vertex:
						classifiedShader[0] = std::move(currentShaderStr);
						break;

					case ShaderType::Fragment:
						classifiedShader[1] = std::move(currentShaderStr);
						break;

					case ShaderType::Geometry:
						classifiedShader[2] = std::move(currentShaderStr);
						break;
					}

					currentShaderStr.clear();
				}

				if (line.compare(0, ShaderAsset::VertexShaderMacros.size(), ShaderAsset::VertexShaderMacros, 0) == 0)
				{
					currentShaderType = ShaderType::Vertex;
					isMacros = true;
				}
				else if (line.compare(0, ShaderAsset::FragmentShaderMacros.size(), ShaderAsset::FragmentShaderMacros, 0) == 0)
				{
					currentShaderType = ShaderType::Fragment;
					isMacros = true;
				}
				else if (line.compare(0, ShaderAsset::GeometryShaderMacros.size(), ShaderAsset::GeometryShaderMacros, 0) == 0)
				{
					currentShaderType = ShaderType::Geometry;
					isMacros = true;
				}

				continue;
			}
		}
		
		

		if (currentShaderType != ShaderType::None)
		{
			currentShaderStr += line; // getline stil contain newline character(\n)
			currentShaderStr += '\n';
		}
	}

	if (currentShaderStr.size() != 0)
	{
		switch (currentShaderType)
		{
		case ShaderType::Vertex:
			classifiedShader[0] = std::move(currentShaderStr);
			break;

		case ShaderType::Fragment:
			classifiedShader[1] = std::move(currentShaderStr);
			break;

		case ShaderType::Geometry:
			classifiedShader[2] = std::move(currentShaderStr);
			break;
		}

		currentShaderStr.clear();
	}

	return classifiedShader;
	
}


bool doom::asset::ShaderAsset::CheckIsSharpInclude(const std::string& str)
{
	std::string trimedStr = std::trim(str, ' ');
	if (trimedStr.compare(0, 1, "#") == 0)
	{// macros shouldn't have whitespace

		if (trimedStr.compare(0, 8, "#include") == 0)
		{// To Support #include in GLSL
			return true;
		}
	}

	return false;
}

std::string doom::asset::ShaderAsset::ExtractShaderFile(const std::filesystem::path& path)
{
	std::stringstream inputStringStream{ GetTextFromFile(path) };
	std::string line;

	std::string extractedShaderText{};

	while (std::getline(inputStringStream, line))
	{
		if (CheckIsSharpInclude(line))
		{
			std::filesystem::path targetPath = path;//
			targetPath.remove_filename();

			std::string includeTargetPath = line.substr(line.find("#include", 0) + 8, std::string::npos);
			includeTargetPath = std::trim(includeTargetPath, "\r");
			includeTargetPath = std::trim(includeTargetPath, ' ');
			targetPath.append(includeTargetPath);

			extractedShaderText += ExtractShaderFile(targetPath.make_preferred().string());
		}
		else
		{
			extractedShaderText += line;
		}
		extractedShaderText += '\n';
	}
	
	return extractedShaderText;
}

void doom::asset::ShaderAsset::checkCompileError(unsigned int id, ShaderType shaderType)
{
	int success;
	char infoLog[1024];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	std::string shaderTypeStr{};
	if (shaderType == ShaderType::Vertex)
	{
		shaderTypeStr = "Vertex Shader";
	}
	else if (shaderType == ShaderType::Vertex)
	{
		shaderTypeStr = "Fragment Shader";

	}
	else if (shaderType == ShaderType::Vertex)
	{
		shaderTypeStr = "Geometry Shader";
	}

	if (!success)
	{
		glGetShaderInfoLog(id, 1024, NULL, infoLog);
		D_DEBUG_LOG({ GetAssetFileName(), "ERROR::SHADER_COMPILATION_ERROR of type: ", shaderTypeStr.c_str(), "\n", infoLog, "\n -- --------------------------------------------------- -- " });
	}
}


bool doom::asset::ShaderAsset::GetIsValid()
{
	return mVertexId || mFragmentId || mGeometryId;
}

void doom::asset::ShaderAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING("Compile Shader", eProfileLayers::Rendering);
	CompileShaders(mShaderFileText);
	D_END_PROFILING("Compile Shader");
}

unsigned int doom::asset::ShaderAsset::GetVertexId()
{
	return mVertexId;
}

unsigned int doom::asset::ShaderAsset::GetFragmentId()
{
	return mFragmentId;
}

unsigned int doom::asset::ShaderAsset::GetGeometryId()
{
	return mGeometryId;
}

