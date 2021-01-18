#include "Shader.h"
#include "../API/OpenglAPI.h"
#include <sstream>
#include <array>
const std::string Doom::Shader::VertexShaderMacros = "#VERTEX";
const std::string Doom::Shader::FragmentShaderMacros = "#FRAGMENT";
const std::string Doom::Shader::GeometryShaderMacros = "#GEOMETRY";

void Doom::Shader::CompileSpecificShader(const std::string& shaderStr, ShaderType shaderType, unsigned int& shaderId)
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

	this->isCompiled = true;
#ifdef DEBUG_MODE
	this->checkCompileError(shaderId, shaderType);
#endif
}



std::array<std::string, 3> Doom::Shader::ClassifyShader(const std::string& str)
{
	std::istringstream inputStringStream{ str };
	std::string line;

	ShaderType currentShaderType = ShaderType::None;
	std::string currentShaderStr{};

	std::array<std::string, 3> classifiedShader{};

	while (std::getline(inputStringStream, line))
	{
		bool isMacros = false;

		if (line.compare(0, 1, "#") == 0)
		{// macros shouldn't have whitespace

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

			if (line.compare(0, Shader::VertexShaderMacros.size(), Shader::VertexShaderMacros, 0) == 0)
			{
				currentShaderType = ShaderType::Vertex;
				isMacros = true;
			}
			else if (line.compare(0, Shader::FragmentShaderMacros.size(), Shader::FragmentShaderMacros, 0) == 0)
			{
				currentShaderType = ShaderType::Fragment;
				isMacros = true;
			}
			else if (line.compare(0, Shader::GeometryShaderMacros.size(), Shader::GeometryShaderMacros, 0) == 0)
			{
				currentShaderType = ShaderType::Geometry;
				isMacros = true;
			}

			continue;
		}
		

		


		if (currentShaderType != ShaderType::None)
		{
			currentShaderStr += line; // getline stil contain newline character(\n)
		}
	}

	return classifiedShader;
	
}

void Doom::Shader::checkCompileError(unsigned int id, ShaderType shaderType)
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
		DEBUG_LOG({ "ERROR::SHADER_COMPILATION_ERROR of type: ", shaderTypeStr, "\n", infoLog, "\n -- --------------------------------------------------- -- " });
	}
}

Doom::Shader::Shader(const std::string& shaderStr) : vertexId{ 0 }, fragmentId{ 0 }, geometryId{ 0 }, isCompiled{ false }
{
	std::array<std::string, 3> shaders = this->ClassifyShader(shaderStr);
	if (shaders[0].size() != 0)
	{
		this->CompileSpecificShader(shaders[0], ShaderType::Vertex, this->vertexId);
	}

	if (shaders[1].size() != 0)
	{
		this->CompileSpecificShader(shaders[1], ShaderType::Fragment, this->fragmentId);
	}

	if (shaders[2].size() != 0)
	{
		this->CompileSpecificShader(shaders[2], ShaderType::Geometry, this->geometryId);
	}
}


Doom::Shader::Shader(Shader&& shader) noexcept
{
	this->vertexId = shader.vertexId;
	shader.vertexId = 0;

	this->fragmentId = shader.fragmentId;
	shader.fragmentId = 0;

	this->geometryId = shader.geometryId;
	shader.geometryId = 0;

	this->isCompiled = shader.isCompiled;
	shader.isCompiled = false;
}

Doom::Shader& Doom::Shader::operator=(Shader&& shader) noexcept
{
	this->vertexId = shader.vertexId;
	shader.vertexId = 0;

	this->fragmentId = shader.fragmentId;
	shader.fragmentId = 0;

	this->geometryId = shader.geometryId;
	shader.geometryId = 0;

	this->isCompiled = shader.isCompiled;
	shader.isCompiled = false;

	return *this;
}

Doom::Shader::~Shader()
{
	if(this->vertexId != 0)
		glDeleteShader(this->vertexId);

	if (this->fragmentId != 0)
		glDeleteShader(this->fragmentId);

	if (this->geometryId != 0)
		glDeleteShader(this->geometryId);
}
